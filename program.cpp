// import
#include "splashkit.h"
#include "globals.h" // <- added this import
//#include <graphics.h>
#include <cstdlib>
#include "player.h"
#include "obstacle.h"
#include "RAIN.h"
#include "BEE_PLAYER.h"
#include <iostream>
#include <memory>
#include "GameManager.h"
//skm g++ program.cpp player.cpp  obstacle.cpp GameManager.cpp -o game.exe

bitmap background = bitmap_named("images/Background.jpg");
bitmap bee = bitmap_named("images/Bee.png");
bitmap box = bitmap_named("images/box.png");
float player_posx = 550.0f;
float player_posy = 650.0f;
int RIGHT_BOUNDARY = 1200;
int LEFT_BOUNDARY = 0;
int GRAVITY = 3;
int spawn_interval = 60;// Spawn obstacles at a rate of 1 per second
int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 960;
float BEE_SCALE = 0.6;

bool game_started = false;  // Flag to track the game status
bool game_over = false;     // Flag for game over status
int game_time = 0;          // Time in seconds
timer my_timer;

// Function declarations
void start_game();
void update_timer();
void display_timer();
void display_start_screen();
void player_move(Player* player);
void Spawn_obstacle(GameManager& gameManager, int& spawn_timer);
void render(GameManager& gameManager, Player& player);
void check_game_over(GameManager& gameManager,Player& player);
void display_game_over_screen();

void start_game() {
    game_started = true;
    game_over = false;
    Player::set_HP(3);
    
    // Reset obstacles, timer, etc.
    reset_timer(my_timer);  // Reset timer when game starts
    start_timer(my_timer);
}

void update_timer() {
    game_time = timer_ticks(my_timer) / 1000;  // Convert milliseconds to seconds
}

void display_timer() {
    draw_text("Time: " + std::to_string(game_time), COLOR_BLACK, "Arial", 60, 50, 50);
    draw_text("Health:  " + std::to_string(Player::get_HP()), COLOR_BLACK, "Arial", 60, 150, 50);
}

void display_start_screen() {

    draw_text("Press SPACE to Start", COLOR_BLACK, "Arial", 200, 550, 200);
}

void check_game_over(GameManager& gameManager,Player& player) {
    if (Player::get_HP() == 1) {
        player.notify_all_RAINs();
    }
    else if (Player::get_HP() <= 0) {
        game_over = true;
        game_started = false;  // Stop the game
        gameManager.clear_Obstacles();
    }
}

void display_game_over_screen() {
    draw_text("Game Over!", COLOR_RED, "Arial", 48, 510, 450);
    draw_text("Press SPACE to Restart", COLOR_WHITE, "Arial", 32, 510, 500);
}

void player_move(Player* player) {
    if (key_down(RIGHT_KEY) && player->get_x() <= RIGHT_BOUNDARY) {
        player->move_right();
    }
    if (key_down(LEFT_KEY) && player->get_x() >= LEFT_BOUNDARY) {
        player->move_left();
    }
}

void Spawn_obstacle(GameManager& gameManager, int& spawn_timer) {
    spawn_timer++;
    if (spawn_timer >= spawn_interval) {
        spawn_timer = 0;
        int spawn_x = rand() % RIGHT_BOUNDARY;  // Random x-coordinate between 0 and RIGHT_BOUNDARY
        std::shared_ptr<Obstacle> obstacle = std::make_shared<Obstacle>(spawn_x, 0, 2);
        gameManager.addObstacle(obstacle);

    }
}


void render(GameManager& gameManager,Player& player) {
    // Redrawing the bitmap after every clear background and bee
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

    gameManager.updateGameObjects();
}


int main() {
    open_window("BeeFall", WINDOW_WIDTH, WINDOW_HEIGHT);  // Named window beefall and window size
    hide_mouse();  // Hide mouse while cursor is over the game window
    Player player(player_posx, player_posy, 10.0f);  // Initialize player
    // Create game manager and add game objects
    GameManager gameManager;
    gameManager.setPlayer(&player);

    // Timer for obstacle spawning
    int spawn_timer = 0;

    // Initialize timer
    my_timer = create_timer("GameTimer");

    while (!quit_requested()) {
        process_events();
        clear_screen();

        if (!game_started) {
            draw_bitmap(background, 0, 0, option_to_screen());
            drawing_options scale_options = option_scale_bmp(BEE_SCALE+0.1, BEE_SCALE+0.1); // Scale to 40% of original size
            draw_bitmap(bee, player.get_x()-50, player.get_y()-50,scale_options);
            display_start_screen();
            if (key_down(SPACE_KEY)) {
                
                start_game();
            }
            refresh_screen(60);
            continue;  // Skip the rest of the loop until the game starts
        }

        if (game_over) {
            
            display_game_over_screen();
            
            if (key_down(SPACE_KEY)) {
                start_game();  // Restart game
            }
            refresh_screen(60);
            continue;  // Skip the rest of the loop until restart
        }

        player_move(&player);

        // Spawn obstacles
        Spawn_obstacle(gameManager, spawn_timer);
        


        // Render game objects
        render(gameManager,player);

        gameManager.checkCollisions();
        // Update game elements
        
        update_timer();
        display_timer();
        check_game_over(gameManager,player);

        refresh_screen(60);
    }
}
