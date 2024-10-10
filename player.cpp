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

void Player::attach(Observer* observer) {
    observers.push_back(observer);
}

void Player::detach(Observer* observer) {
    auto it = std::remove(observers.begin(), observers.end(), observer);
    if (it != observers.end()) {
        std::cout << "Detaching observer" << std::endl;
        observers.erase(it, observers.end());
    }
}


void Player::notify(Observer* observer, bool is_collision) {
    observer->CollisionUpdate(is_collision); // Call onCollision on the observer, passing this obstacle
}

void Player::notify_all_observers() {
    std::cout << "Notifying all observers..." << std::endl;
    for (Observer* observer : observers) {
        if (observer == nullptr) {
            std::cout << "Observer is null!" << std::endl;
            continue;  // Skip null observers
        }
        observer->deceaseSpeed(1); 
    }
}