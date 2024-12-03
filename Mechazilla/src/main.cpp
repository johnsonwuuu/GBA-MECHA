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

const int FRAME_LIMIT = 60;

enum class GameStage {
    STAGE1,
    STAGE2,
    STAGE3
};

class Booster
{
private:
    bn::fixed x, y;          // Position
    bn::fixed vx, vy;        // Velocity
    bn::fixed ax, ay;        // Acceleration
    bn::fixed theta_r;       // Orientation of the rocket
    bn::fixed omega_r;       // Angular velocity
    bn::fixed alpha_r;       // Angular acceleration
    bn::fixed theta_v;       // Thrust vector angle relative to the rocket
    bn::fixed mass;          // Mass of the booster
    bn::fixed inertia;       // Moment of inertia
    bn::fixed height;        // Height of the booster
    static constexpr bn::fixed GRAVITY = 0.1;   // Reduced gravity
    static constexpr bn::fixed MOVE_SPEED = 1.5; // Increased move speed

public:
    Booster(bn::fixed initial_x, bn::fixed initial_y, bn::fixed booster_mass, bn::fixed booster_inertia, bn::fixed booster_height)
        : x(initial_x), y(initial_y), vx(0), vy(0), ax(0), ay(GRAVITY), theta_r(0), omega_r(0), alpha_r(0), theta_v(0),
          mass(booster_mass), inertia(booster_inertia), height(booster_height)
    {
    }

    void move_left()
    {
        vx = -MOVE_SPEED;
    }

    void move_right()
    {
        vx = MOVE_SPEED;
    }

    void stop_horizontal()
    {
        vx = 0;
    }

    void update(bn::fixed dt)
    {
        // Apply gravity
        vy += ay * dt;

        // Update position
        x += vx * dt;
        y += vy * dt;

        // Update rotation
        omega_r += alpha_r * dt;
        theta_r += omega_r * dt;
    }

    void reset_position(bn::fixed new_x, bn::fixed new_y)
    {
        x = new_x;
        y = new_y;
        vx = 0;
        vy = 0;
        theta_r = 0;
        omega_r = 0;
        alpha_r = 0;
    }

    bn::fixed get_x() const { return x; }
    bn::fixed get_y() const { return y; }
    bn::fixed get_theta_r() const { return theta_r; }
};

int main()
{
    bn::core::init();

    // Initialize with stage1
    GameStage current_stage = GameStage::STAGE1;
    bn::regular_bg_ptr current_bg = bn::regular_bg_items::stage1.create_bg(0, 0);

    // Screen dimensions (GBA screen is 240x160)
    const bn::fixed screen_width = 240;
    const bn::fixed screen_height = 160;
    const bn::fixed sprite_width = 32;  // Increased for better visibility

    // Start position: center of screen horizontally, above the screen vertically
    const bn::fixed start_x = 120;      // Exactly center horizontally
    const bn::fixed start_y = -32;      // Start above screen

    // Booster initialization
    Booster booster(start_x, start_y, 100, 50, 20);
    bn::sprite_ptr booster_sprite = bn::sprite_items::rocket.create_sprite(start_x, start_y);
    
    // Set initial rotation (0 for pointing downward)
    booster_sprite.set_rotation_angle(0);

    while (true)
    {
        // Handle rocket movement
        if(bn::keypad::left_held() && booster.get_x() > 8)
        {
            booster.move_left();
        }
        else if(bn::keypad::right_held() && booster.get_x() < screen_width - 8)
        {
            booster.move_right();
        }
        else
        {
            booster.stop_horizontal();
        }

        // Update rocket physics
        booster.update(0.1);

        // Update sprite position
        booster_sprite.set_position(booster.get_x(), booster.get_y());
        booster_sprite.set_rotation_angle(booster.get_theta_r());

        // Reset position if rocket goes off screen bottom
        if(booster.get_y() > screen_height + sprite_width)
        {
            booster.reset_position(start_x, start_y);
        }

        bn::core::update();
    }

    return 0;
}
