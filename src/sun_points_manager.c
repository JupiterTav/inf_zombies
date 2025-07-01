#include "sun_points_manager.h"
#include "raylib.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>
#define MAX_SUNS 5
SUN suns_spawned[MAX_SUNS];
int spawned_suns = 0;

Texture2D sun_texture;
float framesWidth;
float framesHeight;

Texture2D sun_menu_texture;

static int points = 0;
int Points;
void start_sun_points(){
  if(IsTextureValid(LoadTexture("assets/sprites/sun.png"))){
    sun_texture = LoadTexture("assets/sprites/sun.png");
    framesWidth = (float)(sun_texture.width/FRAMES_PER_LINE);
    framesHeight = (float)(sun_texture.height/LINES);
  }

  if(IsTextureValid(LoadTexture("assets/sprites/sun_menu.png"))){
    sun_menu_texture = LoadTexture("assets/sprites/sun_menu.png");
  }
  for(int i = 0; i < MAX_SUNS; i++){
      suns_spawned[i].collected = 1;
  }
}
int can_sun_spawn(int frames){
  int can_spawn = 0;
  if(frames % (SPAWNTIME*60) == 0 && spawned_suns <= MAX_SUNS){
    can_spawn = 1;
  }
  return can_spawn;
}
void create_sun(float x_pos, float y_pos, int sunflower){
  float sun_position_x = x_pos, sun_position_y = y_pos;
  if(x_pos == 0 && y_pos == 0){
  srand(time(NULL));
    sun_position_x = (float)((rand() % 8)+1) * 70.83581;
    sun_position_y = (float)((rand() % 4)+1)* 94.96970;
  }
  SUN sun = {
  .collected = 0,
  .position.x = sun_position_x,
  .position.y = sun_position_y,
  .hitbox.x = sun_position_x,
  .hitbox.y = sun_position_y,
  .hitbox.height = 30,
  .hitbox.width = 30,
  .sunflower = sunflower,
  };
  

  spawned_suns++;
  int i = 0;
  int found = 0;
  while(found == 0 && i < MAX_SUNS){
    if(suns_spawned[i].collected == 1){ 
      suns_spawned[i] = sun;
      found = 1;
    } 
    i++;
  }
}


void spawn_sun(int frames){
  for(int i = 0; i < MAX_SUNS; i++){
    if(suns_spawned[i].collected == 0)
      animate_sun(frames, suns_spawned[i].position);
  }
}
static void animate_sun(int frames, Vector2 pos){
  float currentFrame = 1;
  Rectangle frame = { 0, 0, currentFrame*framesWidth, framesHeight };
  if(frames % (60) == 0)
    frame.x = currentFrame*framesWidth;
  DrawTextureRec(sun_texture, frame, pos, WHITE);
  currentFrame = (currentFrame == 1) ? 2 : 1;
}

void collect_sun(){
  if(IsKeyPressed(KEY_S)){
    for(int i = 0; i < MAX_SUNS; i++){
      if(suns_spawned[i].collected == 0){
        suns_spawned[i].collected = 1;
        points += 25;
        spawned_suns--;
      }
    }
  } if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    for(int i = 0; i < MAX_SUNS; i++){
      if(suns_spawned[i].collected == 0 && CheckCollisionPointRec(GetMousePosition(), suns_spawned[i].hitbox) && suns_spawned[i].sunflower == 0){
        suns_spawned[i].collected = 1;
        points += 25;
        spawned_suns--;
      }
    }
  }
}
void points_menu(){
  DrawTextureEx(sun_menu_texture, (Vector2){30, 5}, 0, 0.25, WHITE);
  Rectangle points_back = { 25, 65, 80, 25};
  DrawRectangleRounded(points_back, 0.2, 1, (Color){245, 233, 120, 255});
  DrawText(TextFormat("%d", points), 54, 70, 15, BLACK);
}
void decrease_points(int point){
  points -= point;
}
int get_points(){
  return points;
}
