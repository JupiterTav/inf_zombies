#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "grid_manager.h"
#include "horde_manager.h"
#include "peashooter.h"
#include "plant_manager.h"
#include "sun_points_manager.h"
#include "zombie_manager.h"

#define UP_MARGIN 140
#define LEFT_MARGIN 50
enum{
  MENU = 0,
  IN_GAME,
  PAUSED,
}GAME_STATE;


int main() {

  GAME_STATE = IN_GAME;
  int active_peashooter_portraid = 1;
  Vector2 peashotter_portraid_pos = {170, 15};

  int active_sunflower_portraid = 1;
  Vector2 sunflower_portraid_pos = {260, 10};

  Rectangle left_rect = { 10, 0, 500, 100 };
  int frame_counter = 0;

  struct Grid game_grid;
  
  InitWindow(978, 640, "Inf_zombies");
    SetTargetFPS(60);

  Texture2D peashooter_portraid = LoadTexture("assets/sprites/peashooter_portraid.png");
  Texture2D peashooter_portraid_desactivated = LoadTexture("assets/sprites/peashooter_portraid_desactivated.png");
  Texture2D sunflower_portraid = LoadTexture("assets/sprites/sunflower_portraid.png");
  Texture2D sunflower_portraid_desactivated = LoadTexture("assets/sprites/sunflower_portraid_desactivated.png");

  Texture2D background = LoadTexture("assets/sprites/game_background.png");
  Rectangle screen_background = {0, 0, 978, 680};

  initialize_zombies();
  initialize_horde();
  initialize_grid(&game_grid, LEFT_MARGIN, UP_MARGIN, 72, 96);

  start_sun_points();
  
  while(!WindowShouldClose()){ 
    if(GAME_STATE == IN_GAME){
      frame_counter++;

      manage_selected_grid(&game_grid);
      if(get_points() >= 50 && !game_grid.selected_block->theres_plant){
        active_peashooter_portraid = 1;
        active_sunflower_portraid = 1;
        
        if(IsKeyPressed(KEY_J)){
          make_plant(game_grid.selected_block, PEATER);
          decrease_points(50);
        }
        else if(IsKeyPressed(KEY_K)){
          make_plant(game_grid.selected_block, SUNFLOWER);
          decrease_points(50);
        }
      } 
      else {
        active_peashooter_portraid = 0;
        active_sunflower_portraid = 0;
      }

      collect_sun();

      if(can_sun_spawn(frame_counter)){
        create_sun(0,0,0); // parametros {0,0} -> sois em lugares aleatórios
      } 

      update_pea(frame_counter);
      update_plant();
      update_zumbie();

    
      handle_horde(frame_counter);
    }
    BeginDrawing();

      DrawTexturePro(background, (Rectangle){0, 0, 447, 192}, screen_background, (Vector2){0, 0}, 0, WHITE);
      draw_grid();
      draw_outlined_selected_grid(&game_grid);
    
      render_plants();
      render_peas();
      render_zombie();

      spawn_sun(frame_counter);
      DrawRectangleRounded(left_rect, 0.1, 1, (Color){102, 80, 54, 255});
      points_menu();

      if(get_points() >= 50){
        DrawTextureEx(peashooter_portraid, peashotter_portraid_pos, 0, 3, WHITE);
        DrawTextureEx(sunflower_portraid, sunflower_portraid_pos, 0, 3, WHITE);
      }else{
        DrawTextureEx(peashooter_portraid_desactivated, peashotter_portraid_pos, 0, 3, WHITE);
        DrawTextureEx(sunflower_portraid_desactivated, sunflower_portraid_pos, 0, 3, WHITE);
      }

      if(all_clean())
        DrawText("VOCÊ GANHOU!", GetScreenWidth()/2 - GetScreenWidth()/6, GetScreenHeight()/2-50, 64, BLACK);
      
      else if(GAME_STATE == PAUSED)
        DrawText("PAUSED", GetScreenWidth()/2 - GetScreenWidth()/6, GetScreenHeight()/2, 64, BLACK);
      
    EndDrawing(); 
    
    if(IsKeyPressed(KEY_SPACE))
       GAME_STATE = (GAME_STATE == PAUSED && GAME_STATE != MENU) ? IN_GAME : PAUSED;

  }
  
  CloseWindow();

  return 0;
}
