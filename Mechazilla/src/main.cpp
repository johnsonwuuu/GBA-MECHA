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

// NEW:
#include <bn_list.h>
#include <iostream>

const int FRAME_LIMIT = 60;

enum class GameStage {
    STAGE1,
    STAGE2,
    STAGE3
};

class Booster
{
private:
    // New Thrust Tilt(angle that flame is supposed to make wrt the rocket):
    bn::fixed tilt_angle = 15.00;
    bn::fixed tilt = 15.00;
    bn::fixed tilt_rotation = 20.0;  

    bn::fixed x, y;          
    bn::fixed vx, vy;        
    bn::fixed ax, ay;        
    bn::fixed theta_r;       // Rocket rotation angle
    bn::fixed mass;          
    bn::fixed height;        
    // had to remove >.>
    // static constexpr bn::fixed GRAVITY = 0.03;    // Reduced gravity
    // static constexpr bn::fixed WIND_FORCE = 0.04;  
    // static constexpr bn::fixed TURBULENCE = 0.02;   
    // static constexpr bn::fixed ROTATION_SPEED = 2.0;  
    // static constexpr bn::fixed AIR_RESISTANCE = 0.05; // Increased air resistance
    // static constexpr bn::fixed THRUST = 0.05;
    bn::random random;

    // NEW VALUED VARIABLES:
    static constexpr bn::fixed GRAVITY = 3.00;
    static constexpr bn::fixed WIND_FORCE = 0.04;
    static constexpr bn::fixed TURBULENCE = 0.02;
    static constexpr bn::fixed AIR_RESISTANCE = 0.08;
    bn::fixed THRUST = 0.03;
    // static constexpr bn::fixed THRUST = 0.03;
    // NEW VARIABLES:
    bn::fixed ANGULAR_VEL = 0.00;
    bn::fixed ANGULAR_ACC = 0.00;
    bn::fixed inertia = 2;
    
    // DISCRETE TIME VARIABLES:
    bn::fixed time_step = 0.00;         // will be incremented by dt at every game loop
    bn::fixed dt = 1.0 / 59.7275;       // ~0.01673 seconds

    // NEW: Just define a thrust function, that takes in time-step & outputs thrust.
    bn::fixed Update_Thrust(bn::fixed t_step){
        bn::fixed t = t_step;
        bn::fixed new_thrust = -0.02 * (t - 2.00) * (t - 2.00) + 0.06;
        if(t_step > 2.00 && new_thrust < GRAVITY && t_step < 12.00 ){
            new_thrust = GRAVITY;
        }
        return new_thrust;
    }

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(GRAVITY), theta_r(0),
          mass(booster_mass), height(booster_height)
    {
    }

    void move_left()
    {
        // Tilt right
        if(tilt < 45)
        {
            tilt += tilt_rotation;
        }
    }

    void move_right()
    {
        // Tilt left
        if(tilt > -45)
        {
            tilt -= tilt_rotation;
        }
    }

    // NEW–WORKS :)
    void update()
    {
        // Simulated Time step increment:
        time_step += dt;
        // Thrust Update:
        THRUST = 30.00 * Update_Thrust(time_step);
        // Torque Calculation:
        bn::fixed torque = (height / 2) * THRUST * bn::degrees_lut_sin_safe(bn::safe_degrees_angle(tilt));

        // Update Accelerations:
        ax = - 10.0 * (THRUST * bn::degrees_lut_sin_safe(bn::safe_degrees_angle(theta_r - tilt))) / mass;
        ay = - 2.0 * ((THRUST * bn::degrees_lut_cos_safe(bn::safe_degrees_angle(theta_r - tilt))) / mass) + GRAVITY;  // DOSN'T WORK – COSINE TERM!
        ay = GRAVITY;  // WORKS!
        ANGULAR_ACC = torque / inertia;
        // Update Velocities:
        vx += ax * dt;
        vy += ay * dt;
        ANGULAR_VEL += ANGULAR_ACC * dt;
        // Update position & orientation:
        x += vx * dt;
        y += vy * dt;
        theta_r += ANGULAR_VEL * dt;
        tilt = 0.00;
    }

    void reset_position(bn::fixed new_x, bn::fixed new_y)
    {
        x = new_x;
        y = new_y;
        vx = 0;
        vy = 3.5;
        theta_r = 0;
        ANGULAR_VEL = 0.00;
        ANGULAR_ACC = 0.00;
        time_step = 0.00;
        tilt = 0.00;
    }

    bn::fixed get_x() const { return x; }
    bn::fixed get_y() const { return y; }
    int get_theta_r() const { return (bn::safe_degrees_angle(theta_r)).integer(); }  // Returns an angle between [0, 360)
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
    Booster booster(start_x, start_y, 10, 20);
    bn::sprite_ptr booster_sprite = bn::sprite_items::rocket.create_sprite(start_x, start_y);
    booster_sprite.set_rotation_angle(0);

    // Create Mechazilla sprite with initial random position
    bn::fixed mechazilla_x = (random.get() % 160) - 80;
    bn::sprite_ptr mechazilla_sprite = bn::sprite_items::mechazilla.create_sprite(mechazilla_x, 48);


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
            
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                break;

            case GameStage::STAGE3:
             
                if(bn::keypad::left_held() && booster.get_x() > -120)
                {
                    booster.move_left();
                }
                else if(bn::keypad::right_held() && booster.get_x() < 120)
                {
                    booster.move_right();
                }
                break;
        }

        // Update rocket physics
        booster.update();
        booster_sprite.set_position(booster.get_x(), booster.get_y());
        booster_sprite.set_rotation_angle(booster.get_theta_r());

        // Check for out of bounds or bottom hit
        if(booster.get_y() > 80 || booster.get_x() < -120 || booster.get_x() > 120)
        {
            booster.reset_position(start_x, start_y);
            mechazilla_x = (random.get() % 160) - 80;
            mechazilla_sprite.set_x(mechazilla_x);
        }

        // Check for collision between rocket and current Mechazilla position
        if(abs(booster.get_x() - mechazilla_sprite.x()) < 16 && abs(booster.get_y() - 48) < 16)
        {
            // Collision detected
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
                    bn::optional<bn::regular_bg_ptr> ending_bg = bn::regular_bg_items::ending.create_bg(0, 0);
                    
                    // Wait for A button to restart the game
                    while(!bn::keypad::a_pressed())
                    {
                        bn::core::update();
                    }
                    
                    // Clear ending screen
                    ending_bg.reset();
                    
                    // Reset to Stage 1
                    bg1 = bn::regular_bg_items::stage1.create_bg(0, 0);
                    current_stage = GameStage::STAGE1;
                    
                    // Reset sprites
                    mechazilla_sprite.set_visible(true);
                    booster_sprite.set_visible(true);
                    mechazilla_x = (random.get() % 160) - 80;
                    mechazilla_sprite.set_x(mechazilla_x);
                    booster.reset_position(start_x, start_y);
                    break;
            }
        }

        bn::core::update();
    }

    return 0;
}