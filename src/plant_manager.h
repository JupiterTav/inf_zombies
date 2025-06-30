#ifndef PLANT_MANAGER_H
#define PLANT_MANAGER_H
#include "grid_manager.h"
#include <raylib.h>
typedef enum{
  PEATER,
  SUNFLOWER,
}PLANT_TYPE;

typedef enum{
    IDLE,
    SHOOTING,
}STATE;

typedef struct{
  int f_alive;
  int f_shooting;
  Vector2 position;
  Block *block;
  Rectangle hitbox;
  PLANT_TYPE type;
  STATE state;
  Texture2D plant_idle_texture;
  Texture2D plant_shooting_texture;
  Rectangle frame;
  float currentFrame;
}PLANT;
void start_plants();
void make_plant(Block *block_selected, PLANT_TYPE plant_type);
void on_collision();
void update_plant(int frames);
void render_plants(int frames); // Renderiza todas as plantas de um array atráves de uma funçao interna que renderiza uma a uma
void plant_anim(PLANT *plant, int frame_counter, int anim_frames, int anim_speed, int frame_width, int frame_height);
void die(PLANT p);
#endif
