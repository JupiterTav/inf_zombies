#include "peashooter.h"
#include "plant_manager.h"
#include "raylib.h"
#include <stdio.h>


PEA peas[90];
float frameWidth = 13;
float frameHeight = 15;

void shoot_pea(PLANT peashooter_plant){ 
  PEA new_pea = { 
    .activated = 1,
    .pos.x = peashooter_plant.position.x + 20,
    .pos.y = peashooter_plant.position.y - 10,
    .hitbox.height = 10,
    .hitbox.width = 10,
    .pea_texture = LoadTexture("assets/sprites/pea.png"),
    .currentFrame = 0,
    .currentSprite.width = frameWidth,
    .currentSprite.height = frameHeight,
  };
  new_pea.currentSprite.x = frameWidth*new_pea.currentFrame;
  new_pea.currentSprite.y = frameHeight;

  new_pea.hitbox.x = new_pea.pos.x;
  new_pea.hitbox.y = new_pea.pos.y;

  int i = 0;
  while(peas[i].activated == 1)
    i++;
  peas[i] = new_pea;
}

void update_pea(int frames){
  for(int i = 0; i < 90; i++){
    if(peas[i].activated == 1){
      peas[i].pos.x += PEA_SPEED*GetFrameTime();  
      peas[i].hitbox.x = peas[i].pos.x;
    }else{
      peas[i].hitbox.height = 0;
      peas[i].hitbox.width = 0;
        if(frames % (10) == 0){
          peas[i].currentFrame++;
          peas[i].currentSprite.x = frameWidth*peas[i].currentFrame;
          peas[i].currentSprite.y = frameHeight;
        }
    }
  }
}
void render_peas(){
  for(int i = 0; i < 90; i++){
    if(peas[i].activated == 1)
      DrawTextureRec(peas[i].pea_texture, peas[i].currentSprite, peas[i].pos, WHITE);
  }
}
PEA* get_pea(int i){
  return &peas[i];
}
