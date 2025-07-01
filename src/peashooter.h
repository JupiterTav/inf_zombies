#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "plant_manager.h"
#include <raylib.h>
#define Damage 25
#define PEA_SPEED 170
#define COOLDOWN 4

typedef struct{
  Rectangle hitbox;
  Vector2 pos;
  Texture2D pea_texture;
  Rectangle currentSprite;
  float currentFrame;
  int activated;
}PEA; 

void shoot_pea(PLANT peashooter_plant);

void update_pea(int frames);

void render_peas();

#endif
