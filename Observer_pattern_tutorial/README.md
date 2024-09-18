# Tutorial: Implementing the Observer Pattern in a Splashkit Project

## 1. Overview of the Observer Pattern

The Observer Pattern is a behavioral design pattern used to manage and synchronize the state between objects. In this tutorial, we will explore how this pattern is implemented in our game project to handle interactions between the `Player` and `Obstacle` classes.

## 2. Code Structure

### a. Header Files Overview

#### `Subject.h`

- **Purpose:** Defines the `Subject` class, which manages a list of observers and provides methods to attach, detach, and notify them.
- **Key Methods:**
  - `attach(Observer* observer)`
  - `detach(Observer* observer)`
  - `notify(Observer* observer, bool is_collision)`

#### `Observer.h`

- **Purpose:** Defines the `Observer` interface with methods that the `Subject` can call to update observers.
- **Key Methods:**
  - `CollisionUpdate(bool is_collision)`
  - `deceaseSpeed(int newSpeed)`

### b. Class Implementations

#### `Player.h` and `Player.cpp`

- **Purpose:** Implements the `Player` class, which is a `Subject` and notifies its observers about state changes.
- **Key Methods:**
  - `notify(Observer* observer, bool is_collision)`
  - `notify_all_observers()`
  - **Explanation:** How these methods manage the observers list and call their methods.

#### `Obstacle.h` and `Obstacle.cpp`

- **Purpose:** Implements the `Obstacle` class, which is an `Observer` and reacts to notifications from the `Player`.
- **Key Methods:**
  - `CollisionUpdate(bool is_collision)`
  - `deceaseSpeed(int newSpeed)`
  - **Explanation:** How the `Obstacle` updates its state based on notifications.

## 3. Detailed Code Flow Explanation

### a. Attaching Observers

- **In `Player.cpp`:**
  - The `attach` method in `Player` adds an `Observer` to its list.
  - Example:
    ```cpp
    player.attach(&newObstacle);
    ```

### b. Notifying Observers

- **In `Player.cpp`:**
  - **`notify` Method:** Calls `CollisionUpdate` on a specific observer.
  - **`notify_all_observers` Method:** Iterates over all observers and calls `deceaseSpeed`.
  - Example:
    ```cpp
    void Player::notify_all_observers() {
        for (auto observer : observers) {
            observer->deceaseSpeed(newSpeed);
        }
    }
    ```

- **In `Obstacle.cpp`:**
  - **`CollisionUpdate` Method:** Updates the obstacle’s state based on a collision notification.
  - **`deceaseSpeed` Method:** Adjusts the obstacle’s speed based on the player's notification.
  - Example:
    ```cpp
    void Obstacle::CollisionUpdate(bool is_collision) {
        if (is_collision) {
            // Handle collision
        }
    }
    ```

## 4. Example Use Case in Your Game

### Scenario

When an obstacle collides with the player, the `Player` will notify the `Obstacle`:

1. **Collision Detected:** `Player::notify` is called.
2. **Notify All Observers:** `Player::notify_all_observers` updates all attached `Obstacle` instances.
3. **Obstacle Processes Notification:** Each `Obstacle` processes the notification and updates its state.

## 5. Code Demonstration

### Attaching an Observer

```cpp
// Example: Attaching an obstacle to the player
player.attach(&obstacle);
```

### Notifying a Specific Observer
```cpp
// Example: Notifying a specific observer about a collision
player.notify(&obstacle, true);
```

### Notifying All Observers
```cpp
// Example: Notifying all observers about a state change
player.notify_all_observers();
```
## 6.Conclusion
In this tutorial, we explored how the Observer Pattern can be applied to manage interactions between game entities in a Splashkit project. This pattern helps in efficiently managing state changes and interactions, making the codebase more modular and easier to maintain.
