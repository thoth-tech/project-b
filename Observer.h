// observer.h
#ifndef OBSERVER_H
#define OBSERVER_H

class Observer {
public:
    virtual ~Observer() {}
    virtual void CollisionUpdate(bool is_collision)=0;
};

#endif  // OBSERVER_H