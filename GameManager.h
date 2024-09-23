// GameManager.h
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "obstacle.h"
#include <vector>
#include <memory>

class GameManager {
public:
    GameManager();
    void addObstacle(std::shared_ptr<Obstacle> obstacle_ptr);
    void setPlayer(Player* player);
    void checkCollisions();
    void updateGameObjects();
    void clear_Obstacles(){obstacles.clear();};

private:
    Player* player;
    std::vector<std::shared_ptr<Obstacle>> obstacles;
};

#endif // GAMEMANAGER_H
