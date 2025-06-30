#include "plant_manager.h"
#include "grid_manager.h"
#include "peashooter.h"
#include "raylib.h"
#include <stdio.h>
#define MAX_PLANTS GRID_COLUMS*GRID_LINES
#define OFFSET_X 30
#define OFFSET_Y 46

PLANT plants[MAX_PLANTS]; 


void start_plants(){
  for(int i = 0; i < MAX_PLANTS; i++){
    plants[i].f_alive = 0;
    plants[i].position = (Vector2){0, 0};
  }
}

void make_plant(Block *selected_block, PLANT_TYPE plant_type){
  int x_pos = selected_block->tile.x + OFFSET_X;
  int y_pos = selected_block->tile.y + OFFSET_Y;
  PLANT new_plant = {
  .block = selected_block,
  .f_alive = 1,
  .position.x = x_pos,
  .position.y = y_pos,
  .type = plant_type,
  .hitbox.x = x_pos - 10,
  .hitbox.y = y_pos - 20,
  .hitbox.height = 60,
  .hitbox.width = 50,
  .state = IDLE, // 0 = IDLE
  .currentFrame =0,
  .f_shooting = 0,
};
  new_plant.block->theres_plant = 1;
  switch(new_plant.type){
    case PEATER:
      new_plant.plant_idle_texture = LoadTexture("assets/sprites/peashooter.png");
      new_plant.plant_shooting_texture = LoadTexture("assets/sprites/peashooter_shooting.png");
    break;
    case SUNFLOWER:
    break;
  }
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

void update_plant(int frames_count){
  for(int i = 0; i < MAX_PLANTS; i++){
    if(plants[i].f_alive == 1){
      switch (plants[i].type) {
        case PEATER:
          if(plants[i].state == IDLE){
            if(frames_count % (COOLDOWN*60) == 0){
              shoot(plants[i]);
              plants[i].state = SHOOTING;
            }
            else{ 
              plant_anim(&plants[i], frames_count, 8, 8, 28, 30);
            }
          }else if (plants[i].state == SHOOTING){
            plant_anim(&plants[i], frames_count, 3, 10, 28, 30);   
            if(frames_count % 24 == 0)
              plants[i].state = IDLE;
          }
        break;
        case SUNFLOWER:
           
        break;
      }
    }
  }
}

void render_plant(PLANT *plant, int frames_count){
    if(plant->f_alive == 1){
      switch(plant->type){
      case PEATER:
        if(plant->state == IDLE)
          DrawTexturePro(plant->plant_idle_texture, plant->frame, plant->hitbox, (Vector2){0, 0}, 0, WHITE);
        else if(plant->state == SHOOTING)
          DrawTexturePro(plant->plant_shooting_texture, plant->frame, plant->hitbox, (Vector2){0, 0}, 0, WHITE);
          break;
      case SUNFLOWER:
          DrawCircle(plant->position.x, plant->position.y, 20, YELLOW);
        break;
      }
    }
}
void render_plants(int frames_count){
  for(int i = 0; i < MAX_PLANTS; i++){
    render_plant(&plants[i], frames_count);
  }
}

void plant_anim(PLANT *plant, int frame_counter, int anim_frames, int anim_speed, int frame_width, int frame_height){ 
 if(frame_counter % anim_speed == 0){
    plant->currentFrame++;
    if(plant->currentFrame >= anim_frames)
      plant->currentFrame = 0;
    plant->frame.x = frame_width*plant->currentFrame;
    plant->frame.y = frame_height;
    plant->frame.width = frame_width;
    plant->frame.height = frame_height;
  }
}
void die(PLANT p){
  printf("plant dead");
  p.f_alive = 0; 
}
