#include "vector"
#include "bn_core.h"
#include "bn_sprite_ptr.h"
#include "bn_math.h"
#include "bn_fixed.h"
#include "bn_sprite_items_mechazilla.h"
#include "bn_regular_bg_ptr.h"
#include "bn_regular_bg_items_stage1.h"
#include "bn_regular_bg_items_stage2.h"
#include "bn_regular_bg_items_stage3.h"
#include "bn_keypad.h"
#include "bn_sprite_items_rocket.h"
#include "bn_optional.h"
#include "bn_random.h"
#include "bn_regular_bg_items_goodintro.h"
#include "bn_regular_bg_items_ending.h"

const int FRAME_LIMIT = 60;

enum class GameStage {
    STAGE1,
    STAGE2,
    STAGE3
};

class Booster
{
private:
    bn::fixed x, y;          
    bn::fixed vx, vy;        
    bn::fixed ax, ay;        
    bn::fixed theta_r;       // Rocket rotation angle
    bn::fixed mass;          
    bn::fixed height;        
    static constexpr bn::fixed GRAVITY = 0.03;    // Reduced gravity
    static constexpr bn::fixed WIND_FORCE = 0.04;  
    static constexpr bn::fixed TURBULENCE = 0.02;   
    static constexpr bn::fixed ROTATION_SPEED = 2.0;  
    static constexpr bn::fixed AIR_RESISTANCE = 0.05; // Increased air resistance
    static constexpr bn::fixed THRUST = 0.05;    
    bn::random random;

    // Helper function to normalize angle (marked as const)
    int normalize_angle(int angle) const
    {
        while(angle < 0) 
        {
            angle += 360;
        }
        while(angle >= 360) 
        {
            angle -= 360;
        }
        return angle;
    }

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(GRAVITY), theta_r(0),
          mass(booster_mass), height(booster_height)
    {
    }

    void move_left()
    {
        // Tilt left
        if(theta_r > -45)
        {
            theta_r -= ROTATION_SPEED;
        }
    }

    void move_right()
    {
        // Tilt right
        if(theta_r < 45)
        {
            theta_r += ROTATION_SPEED;
        }
    }

    void update()
    {
        // Apply gravity
        vy += GRAVITY;

        // Calculate horizontal movement based on tilt
        if(theta_r < 0)  // Tilted left
        {
            vx -= THRUST;
        }
        else if(theta_r > 0)  // Tilted right
        {
            vx += THRUST;
        }

        // Apply air resistance
        vx *= (1 - AIR_RESISTANCE);
        vy *= (1 - AIR_RESISTANCE);

        // Update position
        x += vx;
        y += vy;
    }

    void apply_wind(bool direction, GameStage current_stage)
    {
        bn::fixed wind_multiplier;
        
        switch(current_stage)
        {
            case GameStage::STAGE1:
                wind_multiplier = 0;  // No wind in stage 1
                break;
            case GameStage::STAGE2:
                wind_multiplier = 2;  // Normal wind in stage 2
                break;
            case GameStage::STAGE3:
                wind_multiplier = 1;  // Reduced wind in stage 3
                break;
        }

        if(direction)
        {
            vx += WIND_FORCE * wind_multiplier;
        }
        else
        {
            vx -= WIND_FORCE * wind_multiplier;
        }
    }

    void apply_turbulence()
    {
        vx += (random.get() % 200 - 100) * TURBULENCE / 100;
    }

    void reset_position(bn::fixed new_x, bn::fixed new_y)
    {
        x = new_x;
        y = new_y;
        vx = 0;
        vy = 0;
        theta_r = 0;
    }

    bn::fixed get_x() const { return x; }
    bn::fixed get_y() const { return y; }
    int get_theta_r() const { return normalize_angle(theta_r.integer()); }  // Return normalized angle
};

int main()
{
    bn::core::init();

    // Initialize intro background with goodintro
    bn::optional<bn::regular_bg_ptr> intro_bg = bn::regular_bg_items::goodintro.create_bg(0, 0);

    // Wait for A button press to start game
    while(!bn::keypad::a_pressed())
    {
        bn::core::update();
    }

    // Clear intro screen
    intro_bg.reset();

    // Initialize stage1 background after intro
    GameStage current_stage = GameStage::STAGE1;
    bn::optional<bn::regular_bg_ptr> bg1 = bn::regular_bg_items::stage1.create_bg(0, 0);
    bn::optional<bn::regular_bg_ptr> bg2;
    bn::optional<bn::regular_bg_ptr> bg3;

    // Screen dimensions (GBA screen is 240x160)
    const bn::fixed screen_width = 240;
    const bn::fixed screen_height = 160;
    const bn::fixed sprite_width = 32;

    // Start position: center horizontally (0), top of screen (-80)
    const bn::fixed start_x = 0;
    const bn::fixed start_y = -80;

    // Initialize random number generator
    bn::random random;

    // Booster initialization
    Booster booster(start_x, start_y, 100, 20);
    bn::sprite_ptr booster_sprite = bn::sprite_items::rocket.create_sprite(start_x, start_y);
    booster_sprite.set_rotation_angle(0);

    // Create Mechazilla sprite with initial random position
    bn::fixed mechazilla_x = (random.get() % 160) - 80;
    bn::sprite_ptr mechazilla_sprite = bn::sprite_items::mechazilla.create_sprite(mechazilla_x, 48);

    // Add wind direction toggle with faster changes
    bool wind_right = true;
    int wind_counter = 0;
    const int WIND_CHANGE_RATE = 30;

    while (true)
    {
        // Handle rocket movement based on current stage
        switch(current_stage)
        {
            case GameStage::STAGE1:
                // Basic movement
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                break;

            case GameStage::STAGE2:
                // Stage 2: Stronger wind effect
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                
                // More frequent wind changes
                wind_counter++;
                if(wind_counter >= WIND_CHANGE_RATE)
                {
                    wind_counter = 0;
                    wind_right = !wind_right;
                }
                booster.apply_wind(wind_right, current_stage);
                break;

            case GameStage::STAGE3:
                // Stage 3: Wind and strong horizontal turbulence
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                
                booster.apply_wind(wind_right, current_stage);
                booster.apply_turbulence();  // Now only affects horizontal movement
                break;
        }

        // Update rocket physics
        booster.update();
        booster_sprite.set_position(booster.get_x(), booster.get_y());
        booster_sprite.set_rotation_angle(booster.get_theta_r());

        // Check for collision between rocket and current Mechazilla position
        if(abs(booster.get_x() - mechazilla_sprite.x()) < 16 && abs(booster.get_y() - 48) < 16)
        {
            // Collision detected! Move to next stage
            switch(current_stage)
            {
                case GameStage::STAGE1:
                    bg1.reset();
                    bg2 = bn::regular_bg_items::stage2.create_bg(0, 0);
                    current_stage = GameStage::STAGE2;
                    mechazilla_x = (random.get() % 160) - 80;
                    mechazilla_sprite.set_x(mechazilla_x);
                    booster.reset_position(start_x, start_y);
                    break;
                    
                case GameStage::STAGE2:
                    bg2.reset();
                    bg3 = bn::regular_bg_items::stage3.create_bg(0, 0);
                    current_stage = GameStage::STAGE3;
                    mechazilla_x = (random.get() % 160) - 80;
                    mechazilla_sprite.set_x(mechazilla_x);
                    booster.reset_position(start_x, start_y);
                    break;
                    
                case GameStage::STAGE3:
                    // Clear everything
                    bg3.reset();
                    mechazilla_sprite.set_visible(false);
                    booster_sprite.set_visible(false);
                    
                    // Create ending background
                    bn::regular_bg_ptr ending_bg = bn::regular_bg_items::ending.create_bg(0, 0);
                    
                    // Freeze on ending screen
                    while(true)
                    {
                        bn::core::update();
                    }
            }
        }
        else if(booster.get_y() > 80)
        {
            booster.reset_position(start_x, start_y);
        }

        bn::core::update();
    }

    return 0;
}
