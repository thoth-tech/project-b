### Introduction
The observer pattern is a design pattern used to allow an object (the subject) to notify other objects (observers) of any state changes. This pattern is particularly useful in game development for managing interactions between different components.

### Project Overview
In this tutorial, we will implement the observer pattern in a simple game using SplashKit. Our game will feature a `Player` object and multiple `Obstacle` objects. The `Player` will act as the subject that notifies obstacles of collisions.

### Code Walkthrough
#### Observer Class
The `Observer` class is responsible for handling updates from the subject. Here’s the code:

```cpp
class Observer {
public:
    virtual void CollisionUpdate() = 0;
    virtual void deceaseSpeed() = 0;
};
```

Subject Class
The Subject class maintains a list of observers and notifies them of any changes.
```
class Subject {
private:
    std::vector<Observer*> observers;
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }
    
    void notify_all() {
        for (Observer* observer : observers) {
            observer->CollisionUpdate();
        }
    }
};

```
### Integration with SplashKit
In our game, we use SplashKit to handle rendering and game logic. The observer pattern helps manage game state updates and interactions.

```cpp
void render(std::vector<std::unique_ptr<Obstacle>>& obstacles, Player& player) {
    // Code to render the game objects
}

```

### Practical Examples
In our game, when an obstacle collides with the player, the player’s speed decreases. This is achieved through the observer pattern where obstacles are notified of collisions and respond accordingly.


