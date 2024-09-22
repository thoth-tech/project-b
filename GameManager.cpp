// GameManager.cpp
#include "GameManager.h"
#include "splashkit.h"

GameManager::GameManager() {
    player = nullptr;
}

void GameManager::setPlayer(Player* player) {
    this->player = player;
}

void GameManager::addObstacle(Obstacle* obstacle) {
    obstacles.push_back(std::move(obstacle));
    player->attach(obstacle.get());  // Attach the newly created obstacle
}

void GameManager::checkCollisions() {
    if (player == nullptr) return;
    
    for (auto* obstacle : obstacles) {
        if (player->get_x() < obstacle->get_x() + obstacle->get_width() &&
            player->get_x() + player->get_width() > obstacle->get_x() &&
            player->get_y() < obstacle->get_y() + obstacle->get_height() &&
            player->get_y() + player->get_height() > obstacle->get_y()) 
        {
            // Notify player and obstacle about the collision
            player->notify(obstacle, true);  // The player has collided with the obstacle
        }
    }
}

void GameManager::updateGameObjects() {
    for (auto* obstacle : obstacles) {
        obstacle->update();
    }
}
