#include "sun_points_manager.h"
#include "raylib.h"
#include "stdlib.h"
#include "time.h"
#include <stdio.h>

SUN suns_spawned[10];
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

  SUN sun = {
  .collected = 0,
  .position.x = random_x,
  .position.y = random_y,
  .hitbox.x = random_x,
  .hitbox.y = random_y,
  .hitbox.height = 30,
  .hitbox.width = 30,
  };

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

void spawn_sun(int frames){
  for(int i = 0; i < 10; i++){
    if(suns_spawned[i].collected == 0){
      sun_animated(frames, suns_spawned[i].position);
    }
  }
}
void sun_animated(int frames, Vector2 pos){
  float currentFrame = 1;
  Rectangle frame = { 0, 0, currentFrame*framesWidth, framesHeight };
  if(frames % (20) == 0)
    frame.x = currentFrame*framesWidth;
  DrawTextureRec(sun_texture, frame, pos, WHITE);
  currentFrame = (currentFrame == 1) ? 2 : 1;
}
void collect_sun(){
  if(IsKeyPressed(KEY_S)){
    for(int i = 0; i < 10; i++){
      if(suns_spawned[i].collected == 0){
        suns_spawned[i].collected = 1;
        points += 25;
        spawned_suns--;
      }
    }
  } else if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    for(int i = 0; i < 10; i++){
      if(suns_spawned[i].collected == 0 && CheckCollisionPointRec(GetMousePosition(), suns_spawned[i].hitbox)){
        suns_spawned[i].collected = 1;
        points += 25;
        spawned_suns--;
      }
    }
  }
}
void points_menu(){
  DrawTextureEx(sun_menu_texture, (Vector2){30, 585}, 0, 0.25, WHITE);
  Rectangle points_back = { 25, 645, 80, 25};
  DrawRectangleRounded(points_back, 0.2, 1, (Color){245, 233, 120, 255});
  DrawText(TextFormat("%d", points), 54, 652, 15, BLACK);
}
void decrease_points(int point){
  points -= point;
}
int get_points(){
  return points;
}
