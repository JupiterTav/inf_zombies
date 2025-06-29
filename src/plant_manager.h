#ifndef PLANT_MANAGER_H
#define PLANT_MANAGER_H
#include "grid_manager.h"
#include <raylib.h>
typedef enum{
  PEATER,
  SUNFLOWER,
}PLANT_TYPE;

typedef struct{
  int f_alive;
  Vector2 position;
  Block *block;
  Rectangle hitbox;
  PLANT_TYPE type;
}PLANT;

void start_plants();
void make_plant(Block *block_selected, PLANT_TYPE plant_type);
void on_collision();
void render_plants(); // Renderiza todas as plantas de um array atráves de uma funçao interna que renderiza uma a uma
void die(PLANT p);
#endif
