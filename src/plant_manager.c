#include "plant_manager.h"
#include "grid_manager.h"

#include "peashooter.h"
#include "sun_points_manager.h"
#include "raylib.h"
#include <stdio.h>
#define MAX_PLANTS GRID_COLUMS*GRID_LINES
#define OFFSET_X 30
#define OFFSET_Y 46

PLANT plants[MAX_PLANTS]; 

static void set_textures(PLANT *plant);
static void render_plant(PLANT *plant);

static void plant_anim(PLANT *plant, int anim_frames, int anim_speed, int frame_width, int frame_height);
static void handle_sunflower(int i);
static void handle_peashooter(int i);

void make_plant(Block *selected_block, PLANT_TYPE plant_type){
  int x_pos = selected_block->tile.x + OFFSET_X;
  int y_pos = selected_block->tile.y + OFFSET_Y;
  selected_block->theres_plant = 1;
  PLANT new_plant = {
  .block = selected_block,
  .f_alive = 1,
  .position = {x_pos, y_pos},
  .type = plant_type,
  .hitbox = {x_pos - 10, y_pos - 20, 50, 60},
  .state = IDLE, // 0 = IDLE
  .currentFrame =1,
  .local_frame_counter = 0,
};

  set_textures(&new_plant);
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

void update_plant(){
  for(int i = 0; i < MAX_PLANTS; i++){
    if(plants[i].f_alive == 1){
      switch (plants[i].type) {
        case PEATER:
          handle_peashooter(i);
                  break;
        case SUNFLOWER:
          handle_sunflower(i);
        break;
      }
      plants[i].local_frame_counter++;
    }
  }
}

void render_plants(){
  for(int i = 0; i < MAX_PLANTS; i++){
    render_plant(&plants[i]);
  }
}

static void handle_sunflower(int i){
  plant_anim(&plants[i], 6, 15, 28, 30);
  if(plants[i].state == IDLE){
    if(plants[i].local_frame_counter % (COOLDOWN*60) == 0){
      create_sun(plants[i].position.x, plants[i].position.y+30, 1); 
      plants[i].state = SHOOTING;
    }
  } 
  else if(plants[i].state == SHOOTING){
    if(IsKeyPressed(KEY_S)){
      plants[i].state = IDLE;
      plants[i].local_frame_counter = 0;
    }
  }
}

static void handle_peashooter(int i){
  if(plants[i].state == IDLE){
    if(plants[i].local_frame_counter % (COOLDOWN*60) == 0){
      shoot_pea(plants[i]);
      plants[i].state = SHOOTING;
    } else{ 
      plant_anim(&plants[i], 8, 16, 28, 30);
    }
  } else if (plants[i].state == SHOOTING){
      plant_anim(&plants[i], 3, 10, 28, 30);   
      if(plants[i].local_frame_counter % 24 == 0)
        plants[i].state = IDLE;
    }
}

static void plant_anim(PLANT *plant, int anim_frames, int anim_speed, int frame_width, int frame_height){ 
 if(plant->local_frame_counter % (anim_speed) == 0){
    plant->currentFrame++;
    if(plant->currentFrame >= anim_frames)
      plant->currentFrame = 0;
    plant->frame.x = frame_width*plant->currentFrame;
    plant->frame.y = frame_height;
    plant->frame.width = frame_width;
    plant->frame.height = frame_height;
  }
}

static void set_textures(PLANT *plant){
  switch(plant->type){
    case PEATER:
      plant->plant_idle_texture = LoadTexture("assets/sprites/peashooter.png");
      plant->plant_shooting_texture = LoadTexture("assets/sprites/peashooter_shooting.png");
    break;
    case SUNFLOWER:
      plant->plant_idle_texture = LoadTexture("assets/sprites/sunflower.png");
    break;
  }

}static void render_plant(PLANT *plant){
    if(plant->f_alive == 1){
      switch(plant->type){
      case PEATER:
        if(plant->state == IDLE)
          DrawTexturePro(plant->plant_idle_texture, plant->frame, plant->hitbox, (Vector2){0, 0}, 0, WHITE);
        else if(plant->state == SHOOTING)
          DrawTexturePro(plant->plant_shooting_texture, plant->frame, plant->hitbox, (Vector2){0, 0}, 0, WHITE);
          break;
      case SUNFLOWER:
         DrawTexturePro(plant->plant_idle_texture, plant->frame, plant->hitbox, (Vector2){0, 0}, 0 , WHITE);
        break;
      }
    }
}



