#ifndef SUN_POINTS_MANAGER_H
#define SUN_POINTS_MANAGER_H
#include "raylib.h"

#define SPAWNTIME 4
#define POINTS 25

typedef struct{
  Rectangle hitbox;
  Vector2 position;
  int collected;
}SUN;
void start_sun_points();
int can_sun_spawn(int frames);
void create_sun();
void spawn_sun();
void collect_sun();

#endif // !DEBUG
