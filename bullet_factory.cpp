    #include "bullet_factory.h"
    #include "globals.h"
    #include <cmath>
    #include <iostream>

    std::vector<sprite> BulletFactory::SprayProjectiles(ProjectileType type, point_2d origin, vector_2d direction, int count, float spread) {
        std::vector<sprite> bullets;
        
        float angleStep = spread / (count - 1);
        float startAngle = -spread / 2;
        
        for (int i = 0; i < count; i++) {
            float angle = startAngle + i * angleStep;
            vector_2d rotatedDirection = RotateVector(direction, angle);
            
            sprite bullet = CreateBullet(type, origin, rotatedDirection);
            if (bullet) {
                bullets.push_back(bullet);
                std::cout << "Created bullet at (" << sprite_x(bullet) << ", " << sprite_y(bullet) << ")" << std::endl;
            }
        }
        
        return bullets;
    }

    sprite BulletFactory::CreateBullet(ProjectileType type, point_2d origin, vector_2d direction) {
        if (!bitmap_valid(bullet)) {
            std::cout << "Error: Could not load bullet bitmap in CreateBullet" << std::endl;
            return nullptr;
        }

        sprite bullet_sprite = create_sprite(bullet);

        // Scale the sprite
        //sprite_set_scale(bullet_sprite,0.2); // Scale by 50%
        
        sprite_set_position(bullet_sprite, origin);
        
        vector_2d velocity;
        switch (type) {
            case ProjectileType::NORMAL:
                velocity = vector_multiply(direction, 5);
                break;
            case ProjectileType::FAST:
                velocity = vector_multiply(direction, 10);
                break;
            case ProjectileType::EXPLOSIVE:
                velocity = vector_multiply(direction, 3);
                break;
        }
        sprite_set_velocity(bullet_sprite, velocity);
        
        return bullet_sprite;
    }

    vector_2d BulletFactory::RotateVector(vector_2d vec, float angle) {
        float cos_a = std::cos(angle);
        float sin_a = std::sin(angle);
        return vector_2d{
            vec.x * cos_a - vec.y * sin_a,
            vec.x * sin_a + vec.y * cos_a
        };
    }