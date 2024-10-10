// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "Subject.h"
#include "obstacle.h"
#include <vector>
#include "Observer.h"
#include <memory>
class Player : public Subject {

public:
    Player(float x, float y, float speed);
    void move_right();
    void move_left();
    float get_x() { return x; }
    float get_y() { return y; }
    float get_width() { return width; }
    float get_height() { return height; }
    float get_speed() { return speed; }
    static int get_HP(){return HP;}
    static void set_HP(int hp){HP = hp;}
    void attach(Observer* observer) override;
    void detach(class Observer* observer) ;
    void notify(class Observer* observer, bool is_collision);
    void notify_all_observers();
private:
    float x, y, speed, width, height;
    static int HP;  
    std::vector<Observer*> observers;
};

#endif  // PLAYER_H