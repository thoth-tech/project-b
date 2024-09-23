// RAIN.h
#ifndef RAIN_H
#define RAIN_H

class RAIN {
public:
    virtual ~RAIN() {}
    virtual void CollisionUpdate(bool is_collision)=0;
    virtual void deceaseSpeed(int newSpeed)=0;
};

#endif  // RAIN_H