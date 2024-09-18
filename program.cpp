// import
#include "splashkit.h"
#include "globals.h" // <- added this import
//#include <graphics.h>
#include <cstdlib>
#include "player.h"
#include "obstacle.h"
#include "Observer.h"
#include "Subject.h"
#include <iostream>
//skm g++ program.cpp player.cpp  obstacle.cpp -o game.exe

bitmap background = bitmap_named("images/Background.jpg");
bitmap bee = bitmap_named("images/Bee.png");
bitmap box = bitmap_named("images/box.png");
float player_posx = 480.0f;
float player_posy = 550.0f;
int RIGHT_BOUNDARY = 1020;
int LEFT_BOUNDARY = 0;
int GRAVITY = 3;
int spawn_interval = 60;// Spawn obstacles at a rate of 1 per second
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 960;



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
    draw_bitmap(background, 0 , 0 , option_to_screen());
    draw_bitmap(bee, player.get_x(), player.get_y(), option_to_screen());

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

    // Spawn obstacles at a rate of 1 per second
    int spawn_timer = 0;
    
    while (!quit_requested())
    {
        process_events();
        clear_screen();
        
        player_move(&player);
        

        // Spawn obstacle at a random x-coordinate
        Spawn_obstacle(&obstacles,&player,spawn_timer);

        render(obstacles,player);
        refresh_screen(60);
    }
}
