// BEE_PLAYER.h
#ifndef BEE_PLAYER_H
#define BEE_PLAYER_H
#include <vector>
#include <memory>
#include "RAIN.h"  // Include the definition
class RAIN;
class Obstacle;

class BEE_PLAYER {
public:
    virtual ~BEE_PLAYER() {}
    virtual void attach(std::shared_ptr<RAIN> RAIN) = 0;
    virtual void detach(RAIN* RAIN) =0;
    virtual void notify(RAIN* RAIN, bool is_collision) =0;
};

#endif  // BEE_PLAYER_H