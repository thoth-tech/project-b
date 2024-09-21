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
bitmap box = bitmap_named("images/raindrop2.png");
bitmap bullet = bitmap_named("images/pollen.png");
float player_posx = 550.0f;
float player_posy = 650.0f;
int RIGHT_BOUNDARY = 1200;
int LEFT_BOUNDARY = 0;
int GRAVITY = 3;
int spawn_interval = 60;// Spawn obstacles at a rate of 1 per second
float BEE_SCALE = 0.6;

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

void player_move(Player* player){
    if (key_down(RIGHT_KEY) && player->get_x() <= RIGHT_BOUNDARY) {
        player->move_right();
    }
    if (key_down(LEFT_KEY) && player->get_x() >= LEFT_BOUNDARY) {
        player->move_left();
    }
}
void Spawn_obstacle(std::vector<Obstacle>* obstacles,Player* player,int& spawn_timer){
    spawn_timer++;
    if (spawn_timer >= spawn_interval)
    {
        spawn_timer = 0;
        int spawn_x = rand() % RIGHT_BOUNDARY; // Random x-coordinate between 0 and RIGHT_BOUNDARY
        Obstacle newObstacle(spawn_x, 0,2);
        obstacles->push_back(newObstacle);
        player->attach(&newObstacle); // Attach player observer to new obstacle
    }
}

void render(std::vector<Obstacle>& obstacles,Player& player){
    //redrawing the bitmap after every clear background and bee
    double center_x = player.get_x()+(player.get_width()/2);
    double center_y = player.get_y()+(player.get_height()/2);
    draw_bitmap(background, 0, 0, option_to_screen());
    drawing_options scale_options = option_scale_bmp(BEE_SCALE+0.1, BEE_SCALE+0.1); // Scale to 70% of original size
    draw_bitmap(bee, player.get_x()-50, player.get_y()-50,scale_options);

    // Get the circle that encompasses the scaled bitmap

    point_2d bee_position = point_at(center_x,center_y);
    circle scaled_bee_circle = bitmap_cell_circle(bee, bee_position,BEE_SCALE);

    // Draw the circle for debugging
    draw_circle(COLOR_RED,scaled_bee_circle); 

    // Update and draw obstacles
    for (Obstacle& obstacle : obstacles) {
        obstacle.update();
        obstacle.draw();
        handle_collision(player, obstacle);
    }
}

int main()
{
    open_window("BeeFall", 1280, 960); //named window beefall and window size
    hide_mouse(); // hide mouse while cursor is over game window
    Player player(480.0f, 550.0f, 10.0f); // initialize player
    std::vector<Obstacle> obstacles; // list of obstacle
    std::vector<sprite> bullets;

    // Check if bullet bitmap is loaded correctly
    if (!bitmap_valid(bullet)) {
        std::cout << "Error: Could not load bullet bitmap" << std::endl;
        return 1;
    }

    int spawn_timer = 0;
    
    while (!quit_requested())
    {
        process_events();
        clear_screen();
        player_move(&player);
        // Shoot bullets when spacebar is pressed
        if (key_typed(SPACE_KEY)) {
            point_2d origin = point_at(player.get_x()-20+player.get_width()/2, player.get_y()-20+player.get_height()/2); // Adjust based on player sprite size
            vector_2d direction = vector_to(0, -1); // Shoot upwards
            int bulletCount = 5;
            float spreadAngle = 45 * (std::atan(1) * 4 / 180); // 45 degrees in radians
            
            std::vector<sprite> newBullets = BulletFactory::SprayProjectiles(ProjectileType::NORMAL, origin, direction, bulletCount, spreadAngle);
            bullets.insert(bullets.end(), newBullets.begin(), newBullets.end());
            
            std::cout << "Created " << newBullets.size() << " bullets" << std::endl;
        }

        // Spawn obstacle at a random x-coordinate
        Spawn_obstacle(&obstacles,&player,spawn_timer);

        render(obstacles,player);

        // Update and draw bullets
        for (auto it = bullets.begin(); it != bullets.end();) {
            update_sprite(*it);
            
            // Remove bullets that are off-screen
            if (sprite_y(*it) < -50 || sprite_y(*it) > 1010 || sprite_x(*it) < -50 || sprite_x(*it) > 1330) {
                free_sprite(*it);
                it = bullets.erase(it);
            } else {
                draw_sprite(*it);
                
                // Debug: Draw a red circle around each bullet
                // After updating the bullet sprite in your main loop
                point_2d bullet_pos = sprite_position(*it);

                // Get the dimensions of the bullet bitmap
                float bullet_width = bitmap_width(bullet); // Get the bitmap width
                float bullet_height = bitmap_height(bullet); // Get the bitmap height

                // Draw the red circle at the center of the bullet sprite
                fill_circle(COLOR_RED, bullet_pos.x + bullet_width / 2, bullet_pos.y + bullet_height / 2, 5);

                
                ++it;
            }
        }

        // Debug: Display bullet count
        //draw_text("Bullets: " + std::to_string(bullets.size()), COLOR_WHITE, 10, 10);
        

        refresh_screen(60);
    }
}
