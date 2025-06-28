#include "plant_manager.h"
#include "grid_manager.h"
#include "raylib.h"
#include <stdio.h>
#define MAX_PLANTS GRID_COLUMS*GRID_LINES
#define OFFSET_X 36
#define OFFSET_Y 46

PLANT plants[MAX_PLANTS]; 


void start_plants(){
  for(int i = 0; i < MAX_PLANTS; i++){
    plants[i].f_alive = 0;
    plants[i].position = (Vector2){0, 0};
  }
}

void make_plant(Block *selected_block, PLANT_TYPE plant_type){
  PLANT new_plant;
  new_plant.block = selected_block;
  new_plant.block->theres_plant = 1;
  int x_pos = selected_block->tile.x + OFFSET_X;
  int y_pos = selected_block->tile.y + OFFSET_Y;
  new_plant.f_alive = 1;
  new_plant.position.x = x_pos;
  new_plant.position.y = y_pos;
  new_plant.type = plant_type;
  new_plant.hitbox.x = x_pos - 10;
  new_plant.hitbox.y = y_pos - 20;
  new_plant.hitbox.height = 40;
  new_plant.hitbox.width = 30;

  int i = 0;
  while(plants[i].f_alive == 1)
    i++;
  plants[i] = new_plant;
}

void on_collision(){
  for(int i = 0; i < MAX_PLANTS; i++){
    if(CheckCollisionPointRec(GetMousePosition(), plants[i].hitbox)){
      plants[i].f_alive = 0;
      plants[i].block->theres_plant = 0;
    }
  }
}

void render_plant(PLANT plant){
    if(plant.f_alive == 1){
    DrawRectangleLines(plant.hitbox.x, plant.hitbox
                       .y, plant.hitbox.width, plant.hitbox.height, RED);
      switch(plant.type){
      case PEATER:
          DrawCircle(plant.position.x, plant.position.y, 20, DARKGREEN);
          break;
      case SUNFLOWER:
          DrawCircle(plant.position.x, plant.position.y, 20, YELLOW);
        break;
      }
    }
}
void render_plants(){
  for(int i = 0; i < MAX_PLANTS; i++){
    render_plant(plants[i]); 
  }
}

void die(PLANT p){
  printf("plant dead");
  p.f_alive = 0; 
}
