// import
#include "splashkit.h"
#include "globals.h" // <- added this import
#include <cstdlib>
#include "player.h"
#include "obstacle.h"
#include "Observer.h"
#include "Subject.h"
#include <iostream>
#include "bullet_factory.h"
#include <vector>
#include <cmath>
//skm g++ program.cpp player.cpp obstacle.cpp bullet_factory.cpp -o game.exe

bitmap background = bitmap_named("images/Background.jpg");
bitmap bee = bitmap_named("images/Bee.png");
bitmap box = bitmap_named("images/box.png");
bitmap bullet = bitmap_named("images/bullet.png");
float player_posx = 480.0f;
float player_posy = 550.0f;
int RIGHT_BOUNDARY = 1020;
int LEFT_BOUNDARY = 0;
int GRAVITY = 3;
// int spawn_interval = 60;// Spawn obstacles at a rate of 1 per second


bool check_collision(float x1, float y1, float width1, float height1,
                     float x2, float y2, float width2, float height2) {
    // Check if rectangles are colliding
    return (x1 < x2 + width2 &&
            x1 + width1 > x2 &&
            y1 < y2 + height2 &&
            y1 + height1 > y2);
}

// template <typename T, typename U>
// bool is_colliding(T& obj1, U& obj2) {
//     float x1 = obj1.get_x();
//     float y1 = obj1.get_y();
//     float w1 = obj1.get_width();
//     float h1 = obj1.get_height();

//     float x2 = obj2.get_x();
//     float y2 = obj2.get_y();
//     float w2 = obj2.get_width();
//     float h2 = obj2.get_height();

//     // Check for collision
//     return (x1 < x2 + w2 &&
//             x1 + w1 > x2 &&
//             y1 < y2 + h2 &&
//             y1 + h1 > y2);
// }

// // Function to handle collision between two objects
// template <typename T, typename U>
// void handle_collision(T& subject, U& observer) {
//     if (is_colliding(subject, observer)) {
//         if (!observer.get_collision()) { // Collision started
//             subject.notify(&observer,true);
//         }
//         draw_text("Collision detected!", COLOR_BLACK, "Arial", 24, subject.get_x()+10, subject.get_y() - 50);
//     } else {
//         if (observer.get_collision()) { // Collision ended
//             subject.notify(&observer,false);
//         }
//     }
// }

// void player_move(Player* player){
//     if (key_down(RIGHT_KEY) && player->get_x() <= RIGHT_BOUNDARY) {
//         player->move_right();
//     }
//     if (key_down(LEFT_KEY) && player->get_x() >= LEFT_BOUNDARY) {
//         player->move_left();
//     }
// }
// void Spawn_obstacle(std::vector<Obstacle>* obstacles,Player* player,int& spawn_timer){
//     spawn_timer++;
//     if (spawn_timer >= spawn_interval)
//     {
//         spawn_timer = 0;
//         int spawn_x = rand() % RIGHT_BOUNDARY; // Random x-coordinate between 0 and RIGHT_BOUNDARY
//         Obstacle newObstacle(spawn_x, 0,2);
//         obstacles->push_back(newObstacle);
//         player->attach(&newObstacle); // Attach player observer to new obstacle
//     }
// }

// void render(std::vector<Obstacle>& obstacles,Player& player){
//     //redrawing the bitmap after every clear background and bee
//     draw_bitmap(background, 0 , 0 , option_to_screen());
//     draw_bitmap(bee, player.get_x(), player.get_y(), option_to_screen());

//     // Update and draw obstacles
//     for (Obstacle& obstacle : obstacles) {
//         obstacle.update();
//         obstacle.draw();
//         handle_collision(player, obstacle);
//     }
// }

int main()
{
    open_window("BeeFall", 1280, 960); //named window beefall and window size
    hide_mouse(); // hide mouse while cursor is over game window
    Player player(480.0f, 550.0f, 10.0f); // initialize player
    std::vector<Obstacle> obstacles; // list of obstacle
    // std::vector<sprite> bullets;

    // // Check if bullet bitmap is loaded correctly
    // if (!bitmap_valid(bullet)) {
    //     std::cout << "Error: Could not load bullet bitmap" << std::endl;
    //     return 1;
    // }
    // Spawn obstacles at a rate of 1 per second
    int spawn_interval = 60; // 60 frames per second
    int spawn_timer = 0;
    
    while (!quit_requested())
    {
        process_events();
        clear_screen();
        
        if (key_down(RIGHT_KEY) && player.get_x() <= RIGHT_BOUNDARY) {
            player.move_right();
        }
        if (key_down(LEFT_KEY) && player.get_x() >= LEFT_BOUNDARY) {
            player.move_left();
        }
        
        // Shoot bullets when spacebar is pressed
        // if (key_typed(SPACE_KEY)) {
        //     point_2d origin = point_at(player.get_x(), player.get_y()); // Adjust based on player sprite size
        //     vector_2d direction = vector_to(0, -1); // Shoot upwards
        //     int bulletCount = 5;
        //     float spreadAngle = 45 * (std::atan(1) * 4 / 180); // 45 degrees in radians
            
        //     std::vector<sprite> newBullets = BulletFactory::SprayProjectiles(ProjectileType::NORMAL, origin, direction, bulletCount, spreadAngle);
        //     bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
            
        //     std::cout << "Created " << newBullets.size() << " bullets" << std::endl;
        // }

        // Spawn obstacle at a random x-coordinate
        spawn_timer++;
        if (spawn_timer >= spawn_interval)
        {
            spawn_timer = 0;
            int spawn_x = rand() % RIGHT_BOUNDARY; // Random x-coordinate between 0 and RIGHT_BOUNDARY
            Obstacle newObstacle(spawn_x, 0,2);
            obstacles.push_back(newObstacle);
            player.attach(&newObstacle); // Attach player observer to new obstacle
        }

        //redrawing the bitmap after every clear background and bee
        draw_bitmap(background, 0 , 0 , option_to_screen());
        draw_bitmap(bee, player.get_x(), player.get_y(), option_to_screen());

       // Update and draw obstacles
        for (Obstacle& obstacle : obstacles) {
            obstacle.update();
            obstacle.draw();
            // Check for collision with player
            if (check_collision(player.get_x(), player.get_y(), player.get_width(), player.get_height(),
                    obstacle.get_x(), obstacle.get_y(), obstacle.get_width(), obstacle.get_height())) {
                    player.notify(&obstacle,true); // Notify player observer of collision
                    std::cout << "Bee touched the box!" << std::endl;
            }
        }

        // // Update and draw bullets
        // for (auto it = bullets.begin(); it != bullets.end();) {
        //     update_sprite(*it);
            
        //     // Remove bullets that are off-screen
        //     if (sprite_y(*it) < -50 || sprite_y(*it) > 1010 || sprite_x(*it) < -50 || sprite_x(*it) > 1330) {
        //         free_sprite(*it);
        //         it = bullets.erase(it);
        //     } else {
        //         draw_sprite(*it);
                
        //         // Debug: Draw a red circle around each bullet
        //         point_2d bullet_pos = sprite_position(*it);
        //         fill_circle(COLOR_RED, bullet_pos.x+100, bullet_pos.y+180, 5);
                
        //         ++it;
        //     }
        // }

        // Debug: Display bullet count
        //draw_text("Bullets: " + std::to_string(bullets.size()), COLOR_WHITE, 10, 10);
        

        refresh_screen(60);
    }
}
