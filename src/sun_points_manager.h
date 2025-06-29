#ifndef SUN_POINTS_MANAGER_H
#define SUN_POINTS_MANAGER_H
#include "raylib.h"

#define SPAWNTIME 4
#define POINTS 25
#define FRAMES_PER_LINE 2
#define LINES 1
typedef struct{
  Rectangle hitbox;
  Vector2 position;
  int collected;
}SUN;

void start_sun_points();
int can_sun_spawn(int frames);
void create_sun();
void spawn_sun(int frames);
void sun_animated(int frames, Vector2 pos);
void collect_sun();
void points_menu();
void decrease_points(int point);
int get_points();

#endif // !DEBUG
