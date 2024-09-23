// Subject.h
#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
class Observer;
class Obstacle;

class Subject {
public:
    virtual ~Subject() {}
    virtual void attach(std::shared_ptr<Observer> observer) = 0;
    virtual void detach(Observer* observer) =0;
    virtual void notify(Observer* observer, bool is_collision) =0;
};

#endif  // SUBJECT_H