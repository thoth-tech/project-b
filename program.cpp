// import
#include "splashkit.h"
#include "globals.h"  // Keep this from HEAD
#include <cstdlib>
#include "player.h"
#include "obstacle.h"
#include "Observer.h"
#include "Subject.h"
#include <iostream>
#include "bullet_factory.h"  // Keep this from HEAD
#include <memory>  // Keep this from origin/main
#include <vector>
#include <cmath>

//skm g++ program.cpp player.cpp obstacle.cpp bullet_factory.cpp -o game.exe

bitmap background = bitmap_named("images/Background.jpg");
bitmap bee = bitmap_named("images/Bee.png");
bitmap box = bitmap_named("images/box.png");
bitmap bullet = bitmap_named("images/bullet.png");  // Keep this from HEAD

float player_posx = 550.0f;  // Keep the updated player position from origin/main
float player_posy = 650.0f;  // Keep this from origin/main
int RIGHT_BOUNDARY = 1200;   // Keep the updated RIGHT_BOUNDARY from origin/main
int LEFT_BOUNDARY = 0;
int GRAVITY = 3;
int spawn_interval = 60;     // This is the same in both branches
int WINDOW_WIDTH = 1280;     // Keep additional variables from origin/main
int WINDOW_HEIGHT = 960;
float BEE_SCALE = 0.6;

bool game_started = false;   // Keep these from origin/main
bool game_over = false;
int game_time = 0;
timer my_timer;


template <typename T, typename U>
bool is_colliding(T& obj1, U& obj2) {
    float x1 = obj1.get_x();
    float y1 = obj1.get_y();
    float w1 = obj1.get_width();
    float h1 = obj1.get_height();

    float x2 = obj2.get_x();
    float y2 = obj2.get_y();
    float w2 = obj2.get_width();
    float h2 = obj2.get_height();

    // Check for collision
    return (x1 < x2 + w2 &&
            x1 + w1 > x2 &&
            y1 < y2 + h2 &&
            y1 + h1 > y2);
}

// Function to handle collision between two objects
template <typename T, typename U>
void handle_collision(T& subject, U& observer) {
    if (is_colliding(subject, observer)) {
        if (!observer.get_collision()) { // Collision started
            subject.notify(&observer,true);
        }
        draw_text("Collision detected!", COLOR_BLACK, "Arial", 24, subject.get_x()+10, subject.get_y() - 50);
    } else {
        if (observer.get_collision()) { // Collision ended
            subject.notify(&observer,false);
        }
    }
}

void player_move(Player* player) {
    if (key_down(RIGHT_KEY) && player->get_x() <= RIGHT_BOUNDARY) {
        player->move_right();
    }
    if (key_down(LEFT_KEY) && player->get_x() >= LEFT_BOUNDARY) {
        player->move_left();
    }
}

// Keep the bullet shooting logic from HEAD
void shoot_bullets(Player& player, std::vector<sprite>& bullets) {
    if (key_typed(SPACE_KEY)) {
        point_2d origin = point_at(player.get_x(), player.get_y()); // Adjust based on player sprite size
        vector_2d direction = vector_to(0, -1);  // Shoot upwards
        int bulletCount = 5;
        float spreadAngle = 45 * (std::atan(1) * 4 / 180);  // 45 degrees in radians

        std::vector<sprite> newBullets = BulletFactory::SprayProjectiles(ProjectileType::NORMAL, origin, direction, bulletCount, spreadAngle);
        bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());

        std::cout << "Created " << newBullets.size() << " bullets" << std::endl;
    }
}

void Spawn_obstacle(std::vector<std::unique_ptr<Obstacle>>& obstacles, Player* player, int& spawn_timer) {
    spawn_timer++;
    if (spawn_timer >= spawn_interval) {
        spawn_timer = 0;
        int spawn_x = rand() % RIGHT_BOUNDARY;  // Random x-coordinate between 0 and RIGHT_BOUNDARY
        auto newObstacle = std::make_unique<Obstacle>(spawn_x, 0, 2);
        player->attach(newObstacle.get());  // Attach the newly created obstacle
        obstacles.push_back(std::move(newObstacle));  // Move the smart pointer into the vector
    }
}

void render(std::vector<std::unique_ptr<Obstacle>>& obstacles, Player& player, std::vector<sprite>& bullets) {
    // Redraw background and bee
    double center_x = player.get_x() + (player.get_width() / 2);
    double center_y = player.get_y() + (player.get_height() / 2);
    draw_bitmap(background, 0, 0, option_to_screen());
    drawing_options scale_options = option_scale_bmp(BEE_SCALE + 0.1, BEE_SCALE + 0.1);
    draw_bitmap(bee, player.get_x() - 50, player.get_y() - 50, scale_options);

    // Draw obstacles
    for (const auto& obstacle_ptr : obstacles) {
        Obstacle& obstacle = *obstacle_ptr;
        obstacle.update();
        obstacle.draw();
        handle_collision(player, obstacle);
    }

    // Draw bullets
    for (auto it = bullets.begin(); it != bullets.end();) {
        update_sprite(*it);
        if (sprite_y(*it) < -50 || sprite_y(*it) > WINDOW_HEIGHT || sprite_x(*it) < -50 || sprite_x(*it) > WINDOW_WIDTH) {
            free_sprite(*it);
            it = bullets.erase(it);
        } else {
            draw_sprite(*it);
            ++it;
        }
    }
}


int main() {
    open_window("BeeFall", WINDOW_WIDTH, WINDOW_HEIGHT);  // Named window beefall and window size
    hide_mouse();  // Hide mouse while cursor is over the game window
    Player player(player_posx, player_posy, 10.0f);  // Initialize player
    std::vector<std::unique_ptr<Obstacle>> obstacles;  // List of obstacles
    std::vector<sprite> bullets;  // List of bullets

    int spawn_timer = 0;
    my_timer = create_timer("GameTimer");

    while (!quit_requested()) {
        process_events();
        clear_screen();

        if (!game_started) {
            draw_bitmap(background, 0, 0, option_to_screen());
            display_start_screen();
            if (key_down(SPACE_KEY)) {
                start_game();
            }
            refresh_screen(60);
            continue;
        }

        if (game_over) {
            display_game_over_screen();
            if (key_down(SPACE_KEY)) {
                start_game();
            }
            refresh_screen(60);
            continue;
        }

        player_move(&player);
        Spawn_obstacle(obstacles, &player, spawn_timer);
        shoot_bullets(player, bullets);
        render(obstacles, player, bullets);

        update_timer();
        display_timer();
        check_game_over(obstacles, player);

        refresh_screen(60);
    }
}
