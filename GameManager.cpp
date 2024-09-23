// GameManager.cpp
#include "GameManager.h"
#include "splashkit.h"

GameManager::GameManager() {
    player = nullptr;
}

void GameManager::setPlayer(Player* player) {
    this->player = player;
}

void GameManager::addObstacle(std::shared_ptr<Obstacle> obstacle_ptr) {
    obstacles.push_back(obstacle_ptr);
    player->attach(obstacle_ptr);  // Use shared_ptr instead of raw pointer
}

void GameManager::checkCollisions() {
    if (player == nullptr) return;
    
    for (const auto& obstacle_ptr : obstacles) {
        Obstacle& obstacle = *obstacle_ptr;
        if (player->get_x() < obstacle.get_x() + obstacle.get_width() &&
            player->get_x() + player->get_width() > obstacle.get_x() &&
            player->get_y() < obstacle.get_y() + obstacle.get_height() &&
            player->get_y() + player->get_height() > obstacle.get_y()) 
        {
            // Notify player and obstacle about the collision
            if (!obstacle.get_collision()) { // Collision started
                player->notify(&obstacle, true);
                Player::set_HP(Player::get_HP()-1); // Decrease player health on collision
            }
            draw_text("Collision detected!", COLOR_BLACK, "Arial", 24, player->get_x() + 10, player->get_y() - 50);
        }
        else {
            if (obstacle.get_collision()) { // Collision ended
                player->notify(&obstacle, false);
            }
        }
    }
}

void GameManager::updateGameObjects() {
    for (const auto& obstacle_ptr : obstacles) {
        Obstacle& obstacle = *obstacle_ptr;
        obstacle.update();
        obstacle.draw();
    }
}



