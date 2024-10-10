#include "obstacle.h"
#include "globals.h" 
#include "splashkit.h"
#include <algorithm>
#include <iostream>
Obstacle::Obstacle(float x, float y,int speed){
    this->x = x;
    this->y = y;
    this->speed = speed;
    this->width = bitmap_width(box);
    this->height = bitmap_height(box);
    this->collision = false;
}

void Obstacle::update(){
    this->y = this->y + this->speed;
}

void Obstacle::draw() {
    double center_x = this->x + this->width/2;
    double center_y = this->y + this->height/2;
    point_2d box_position = point_at(center_x,center_y);
    circle scaled_box_circle = bitmap_cell_circle(box, box_position,1);
    draw_bitmap(box, x, y, option_to_screen());
    draw_circle(COLOR_RED,scaled_box_circle); 
}

void Obstacle::CollisionUpdate(bool is_collision) {
    this->collision = is_collision;
    if(is_collision){
        std::cout << "Bee touched the box!" << std::endl;
    }
    else{
        std::cout << "collision ends" << std::endl;
    }
    
}

void Obstacle::deceaseSpeed(int newSpeed){
    this->speed = newSpeed;
    std::cout << "The Speed equal to 2 now" << std::endl;
}



