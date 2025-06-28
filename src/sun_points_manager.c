#include "sun_points_manager.h"
#include "raylib.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>

SUN suns_spawned[10];
int spawned_suns = 0;
void start_sun_points(){
  for(int i = 0; i < 10; i++){
      suns_spawned[i].collected = 1;
  }
}
int can_sun_spawn(int frames){
  int can_spawn = 0;
  if(frames % (SPAWNTIME*60) == 0 && spawned_suns <= 10){
    can_spawn = 1;
  }
  return can_spawn;
}
void create_sun(){
  srand(time(NULL));
  float random_x = (float)((rand() % 8)+1) * 72.0;
  float random_y = (float)((rand() % 4)+1)* 96.0;

  SUN sun;
  sun.collected = 0;
  sun.position.x = random_x;
  sun.position.y = random_y;

  spawned_suns++;
  int i = 0;
  int found = 0;
  while(found == 0 && i < 10){
    if(suns_spawned[i].collected == 1){ 
      suns_spawned[i] = sun;
      found = 1;
    } 
    i++;
  }
}

void spawn_sun(){
  for(int i = 0; i < 10; i++){
    if(suns_spawned[i].collected == 0)
      DrawCircle(suns_spawned[i].position.x, suns_spawned[i].position.y, 15, ORANGE);
  }
}

void collect_sun(){
  if(IsKeyPressed(KEY_S)){
    for(int i = 0; i < 10; i++){
      if(suns_spawned[i].collected == 0){
        suns_spawned[i].collected = 1;
        spawned_suns--;
      }
    }
  }
}
