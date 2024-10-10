// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "BEE_PLAYER.h"
#include "obstacle.h"
#include <vector>
#include "RAIN.h"
#include <memory>
class Player : public BEE_PLAYER {

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
    void attach(std::shared_ptr<RAIN> RAIN) override;
    void detach(class RAIN* Rain) ;
    void notify(class RAIN* RAIN, bool is_collision);
    void notify_all_RAINs();
private:
    float x, y, speed, width, height;
    static int HP;  
    std::vector<std::shared_ptr<RAIN>> RAINs;

};

#endif  // PLAYER_H