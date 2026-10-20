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
  Vector2 position;
  Block *block;
  Rectangle hitbox;
  
  PLANT_TYPE type;
  STATE state;
  Texture2D plant_idle_texture;

  int local_frame_counter;
  Texture2D plant_shooting_texture;
  Rectangle frame;
  float currentFrame;
}PLANT;

void make_plant(Block *block_selected, PLANT_TYPE plant_type);
void on_collision(PLANT *plant);
void update_plant();
void render_plants(); // Renderiza todas as plantas de um array atráves de uma funçao interna que renderiza uma a uma
#endif
