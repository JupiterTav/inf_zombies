#include "peashooter.h"
#include "raylib.h"
#include "time.h"
#include <stdio.h>
#include <stdlib.h>
#include "zombie_manager.h"

static void zombie_anim(ZOMBIE *zombie);
ZOMBIE zombies[MAX_ZOMBIES];
void initialize_zombies(){
}
void create_zombie(){

  srand(time(NULL));
  float random_pos_y = ((rand() % 4) + 1) * 96;

  ZOMBIE zombie = {
    .speed = SPEED,
    .life_points = LIFE,
    .position.x = 975,
    .position.y = random_pos_y,
    .hitbox.x = 975,
    .hitbox.y = random_pos_y,
    .hitbox.height = 96,
    .hitbox.width = 72,
    .invunerable_time = INVUNERABLE_TIME,
    .local_frame_counter = 2,
    .current_frame = 0,
  };
  zombie.zombie_texture = LoadTexture("assets/sprites/zombie.png");
  
  int i = 0, found = 0;
  while(zombies[i].life_points > 0)
    i++;
  zombies[i] = zombie;
}

void update_zumbie(){
  for(int i = 0; i < MAX_ZOMBIES; i++){

    if(zombies[i].life_points > 0){
      zombies[i].local_frame_counter++;
      zombies[i].position.x += zombies[i].speed*GetFrameTime();
      zombies[i].hitbox.x = zombies[i].position.x;
      zombies[i].invunerable_time -= 0.1 * GetFrameTime();
      zombie_anim(&zombies[i]); 
    
      for(int j = 0; j < 90; j++){
        if(CheckCollisionRecs(zombies[i].hitbox, get_pea(j)->hitbox) && zombies[i].invunerable_time <= 0){
          zombies[i].life_points -= PEA_DAMAGE;
          zombies[i].invunerable_time = INVUNERABLE_TIME;
          get_pea(j)->activated = 0;
        }
      }
    }
  }
}

void render_zombie(){
  for(int i = 0; i < MAX_ZOMBIES; i++){
    if(zombies[i].life_points > 0)
      DrawTexturePro(zombies[i].zombie_texture, zombies[i].frame, zombies[i].hitbox, (Vector2){0,0}, 0, WHITE);
  }
}

int is_all_dead(){
  int all_dead = 1, i = 0;
  for(int i = 0; i < MAX_ZOMBIES;i++){
    if(zombies[i].life_points > 0){
      all_dead = 0;
      break;
    }
  }

  return all_dead;
}
ZOMBIE* get_zombie(int i){
    return &zombies[i];
}
static void zombie_anim(ZOMBIE *zombie){
  if((zombie->local_frame_counter % 15) == 0){
    zombie->current_frame++;
    if(zombie->current_frame >= 7)
      zombie->current_frame = 0;
    zombie->frame.x = 32*zombie->current_frame; //48 = largura da textura/frames que quero
    zombie->frame.y = 44;
    zombie->frame.width = 32;
    zombie->frame.height = 44;
  }
}




