#include "plant_manager.h"
#include "grid_manager.h"
#include "raylib.h"
#include <stdio.h>
#define MAX_PLANTS GRID_COLUMS*GRID_LINES


PLANT plants[MAX_PLANTS]; 


void start_plants(){
  for(int i = 0; i < MAX_PLANTS; i++){
    plants[i].f_alive = 0;
  }
}

void make_plant(struct Grid game_grid, PLANT_TYPE plant_type){
  PLANT new_plant;
  new_plant.f_alive = 1;
  new_plant.position.x = game_grid.selected_block->tile.x + 36;
  new_plant.position.y = game_grid.selected_block->tile.y + 46;
  new_plant.type = plant_type;
  int i = 0;
  while(plants[i].f_alive == 1)
    i++;
  plants[i] = new_plant;
}

void render_plant(PLANT plant){
  int i = 0;
    if(plant.f_alive == 1){
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
