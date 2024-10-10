#include "player.h"
#include <splashkit.h>
#include "globals.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <vector>

Player::Player(float x, float y, float speed) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->width = bitmap_width(bee)*BEE_SCALE; // Assuming 'bee' is the bitmap for the player
    this->height = bitmap_height(bee)*BEE_SCALE;
}

int Player::HP = 3;  // Initialize the static HP variable

void Player::move_right() {
    
    x += speed;
}

void Player::move_left() {
    
    x -= speed;
    
}

void Player::attach(std::shared_ptr<RAIN> RAIN) {
    RAINs.push_back(RAIN);
}

void Player::detach(RAIN* Rain) {
    auto it = std::remove_if(RAINs.begin(), RAINs.end(),
                             [&Rain](const std::shared_ptr<RAIN>& o) {
                                 return o.get() == Rain;  // Compare the raw pointer
                             });
    RAINs.erase(it, RAINs.end());
}


void Player::notify(RAIN* RAIN, bool is_collision) {
    RAIN->CollisionUpdate(is_collision); // Call onCollision on the RAIN, passing this obstacle
}

void Player::notify_all_RAINs() {
    //std::cout << "Notifying all RAINs..." << std::endl;
    for (auto& RAIN : RAINs) {
        if (!RAIN) {
            std::cout << "RAIN is null!" << std::endl;
            continue;  // Skip null RAINs
        }
        RAIN->deceaseSpeed(1);
    }
}

