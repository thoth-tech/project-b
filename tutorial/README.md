# Tutorial: Combining Design Patterns in the Bee Game Codebase

In this game, we've implemented several design patterns, notably the **Observer** and **Mediator** patterns. These patterns help manage interactions between objects, making the code more modular and easier to maintain. Let's break down how these patterns are used.

---

## Observer Pattern

The **Observer Pattern** allows objects to subscribe to and receive updates from another object. This is particularly useful when you have a one-to-many relationship, such as when multiple obstacles (observers) need to be notified about the player’s status.

### Components Involved:
- **Subject:** The `Player` class acts as the subject.
- **Observers:** The obstacles (`Obstacle` class) act as observers. Each obstacle can be updated when certain conditions are met, such as collisions with the player.

### Implementation:
- **Attaching Observers:**  
  When a new obstacle is added to the game, it's attached to the `Player`:
  ```cpp
  void Player::attach(std::shared_ptr<RAIN> RAIN) {
      RAINs.push_back(RAIN);
  }
    ```
    When a new obstacle is added to the game, it's attached to the Player. This way, the Player maintains a list of observers (obstacles).
- **Notifying Observers:**
```cpp
void Player::notify(RAIN* RAIN, bool is_collision) {
    RAIN->CollisionUpdate(is_collision);
}
```
When the player collides with an obstacle, it calls notify() to update the obstacle's state.
- **Notifying All Observers:**
```cpp
void Player::notify_all_RAINs() {
    for (auto& RAIN : RAINs) {
        RAIN->deceaseSpeed(1);
    }
}
```
This function is used when the player's health drops to a certain level, notifying all obstacles to slow down.


Absolutely! Here’s the entire tutorial wrapped in Markdown code fences, ensuring all sections are properly formatted with closing backticks:

markdown
Copy code
# Tutorial: Combining Design Patterns in the Bee Game Codebase

In this game, we've implemented several design patterns, notably the **Observer** and **Mediator** patterns. These patterns help manage interactions between objects, making the code more modular and easier to maintain. Let's break down how these patterns are used.

---

## Observer Pattern

The **Observer Pattern** allows objects to subscribe to and receive updates from another object. This is particularly useful when you have a one-to-many relationship, such as when multiple obstacles (observers) need to be notified about the player’s status.

### Components Involved:
- **Subject:** The `Player` class acts as the subject.
- **Observers:** The obstacles (`Obstacle` class) act as observers. Each obstacle can be updated when certain conditions are met, such as collisions with the player.

### Implementation:
- **Attaching Observers:**

  ```cpp
  void Player::attach(std::shared_ptr<RAIN> RAIN) {
      RAINs.push_back(RAIN);
  }
When a new obstacle is added to the game, it's attached to the Player. This way, the Player maintains a list of observers (obstacles).

Notifying Observers:

cpp
Copy code
void Player::notify(RAIN* RAIN, bool is_collision) {
    RAIN->CollisionUpdate(is_collision);
}
When the player collides with an obstacle, it calls notify() to update the obstacle's state.

Notifying All Observers:

cpp
Copy code
void Player::notify_all_RAINs() {
    for (auto& RAIN : RAINs) {
        RAIN->deceaseSpeed(1);
    }
}
This function is used when the player's health drops to a certain level, notifying all obstacles to slow down.

**Benefits:**
- **Loose Coupling:** The `Player` doesn’t need to know the specific details of the obstacles; it only knows that they are observers that need to be notified.
- **Scalability:** Adding more obstacles is straightforward without modifying the `Player` class.

---

## Mediator Pattern
The **Mediator Pattern** helps reduce the dependencies between objects by introducing a mediator to handle communication. This pattern is seen in the GameManager class, which mediates interactions between the player and obstacles, such as detecting collisions.

**Components Involved:**
- **Mediator:** The 'GameManager' class is the mediator.
- **Scalability:** The 'Player' and 'Obstacle' classes are the colleagues that communicate through the mediator.

### Implementation:
- **GameManager as Mediator:**

```cpp
void GameManager::addObstacle(std::shared_ptr<Obstacle> obstacle_ptr) {
    obstacles.push_back(obstacle_ptr);
    player->attach(obstacle_ptr);
}
```
The 'GameManager' handles the logic for adding obstacles, setting up the player, and checking for collisions.

- **Handling Collisions:**
```cpp
void GameManager::checkCollisions() {
    for (const auto& obstacle_ptr : obstacles) {
        Obstacle& obstacle = *obstacle_ptr;
        if (player->get_x() < obstacle.get_x() + obstacle.get_width() &&
            player->get_x() + player->get_width() > obstacle.get_x() &&
            player->get_y() < obstacle.get_y() + obstacle.get_height() &&
            player->get_y() + player->get_height() > obstacle.get_y()) {
            
            player->notify(&obstacle, true);
            Player::set_HP(Player::get_HP()-1);
        }
    }
}
```
The 'checkCollisions()' method detects if the player collides with any obstacles and notifies both the player and the obstacle.

**Benefits:**
- **Centralized Logic:** The `GameManager` centralizes the game logic for interactions, making it easier to manage and maintain.
- **Reduced Dependencies:** The player and obstacles don’t need direct references to each other, as the `GameManager` handles their interaction.

---

## Interaction Between Observer and Mediator Patterns

The two patterns work together in the following way:
- **Mediator manages observers:** The `GameManager` (mediator) adds new obstacles and attaches them to the `Player` as observers.
- **Observer pattern updates:** The `Player` then updates these obstacles when collisions happen, or when the player's health changes.

This combination ensures that the game’s objects are loosely coupled, flexible, and easy to extend.
---

## Conclusion
By integrating both the **Observer** and **Mediator** patterns, the game becomes more modular, maintainable, and scalable. The **Observer Pattern** allows the `Player` to communicate with multiple obstacles, while the **Mediator Pattern** in the `GameManager` centralizes control over the interaction logic. These patterns reduce direct dependencies between objects, adhering to the principles of object-oriented design.

As the game grows, other patterns such as **State** or **Strategy** could be incorporated to manage player behavior or obstacle spawning strategies, further improving the design.
