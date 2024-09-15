#include "player.h"
#include <splashkit.h>
#include "globals.h"
#include <iostream>
#include <algorithm>
Player::Player(float x, float y, float speed) {
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->width = bitmap_width(bee); // Assuming 'bee' is the bitmap for the player
    this->height = bitmap_height(bee);
}

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
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void Player::notify(Observer* observer, bool is_collision) {
    observer->CollisionUpdate(is_collision); // Call onCollision on the observer, passing this obstacle
}