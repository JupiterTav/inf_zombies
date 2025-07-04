#ifndef ZOMBIE_MANAGER_H
#define ZOMBIE_MANAGER_H
#include "raylib.h"

#define SPEED -40
#define LIFE 100
#define INVUNERABLE_TIME 0.1f
#define  MAX_ZOMBIES 45

typedef enum{
  ALIVE,
  DEAD
}ZOMBIE_STATE;

typedef struct{
  Vector2 position;
  int life_points;
  float speed;
  Rectangle hitbox;
  
  float invunerable_time;
  int local_frame_counter;

  int current_frame;
  Rectangle frame;
  Texture2D zombie_texture;

  ZOMBIE_STATE state;
}ZOMBIE;

void initialize_zombies();
void create_zombie();
void update_zumbie();
void render_zombie();
int is_all_dead();
ZOMBIE* get_zombie(int i);
#endif
