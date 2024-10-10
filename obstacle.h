// Obstacle.h
#ifndef OBSTACLE_H
#define OBSTACLE_H

#include"Observer.h"
#include "player.h"
class Obstacle : public Observer {
public:
    Obstacle(float x, float y,int speed);
    float get_x() { return x; }
    float get_y() { return y; }
    float get_width() { return width; }
    float get_height() { return height; }
    bool get_collision(){return collision;}
    void update();
    void draw();
    void CollisionUpdate(bool is_collision);
    

private:
    float x, y, width, height, speed;
    bool collision;
    
};

#endif  // OBSTACLE_H