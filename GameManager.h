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
    void addObstacle(Obstacle* obstacle);
    void setPlayer(Player* player);
    void checkCollisions();
    void updateGameObjects();

private:
    Player* player;
    std::vector<std::unique_ptr<Obstacle>> obstacles;
};

#endif // GAMEMANAGER_H
