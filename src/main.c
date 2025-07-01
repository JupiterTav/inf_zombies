#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "grid_manager.h"
#include "peashooter.h"
#include "plant_manager.h"
#include "sun_points_manager.h"

int main() {

  int active_peashooter_portraid = 1;
  Vector2 peashotter_portraid_pos = {170, 15};
  int active_sunflower_portraid = 1;
  Vector2 sunflower_portraid_pos = {260, 10};
  Rectangle left_rect = { 10, 0, 500, 100 };
  SetTargetFPS(60);
  int frame_counter = 0;

  struct Grid game_grid;
  
  InitWindow(978, 640, "Inf_zombies");
  Texture2D peashooter_portraid = LoadTexture("assets/sprites/peashooter_portraid.png");
  Texture2D peashooter_portraid_desactivated = LoadTexture("assets/sprites/peashooter_portraid_desactivated.png");
  Texture2D sunflower_portraid = LoadTexture("assets/sprites/sunflower_portraid.png");
  Texture2D sunflower_portraid_desactivated = LoadTexture("assets/sprites/sunflower_portraid_desactivated.png");

  Texture2D background = LoadTexture("assets/sprites/game_background.png");
  Rectangle screen_background = {0, 0, 978, 680};
  initialize_grid(&game_grid, 50, 140, 72, 96);

  start_sun_points();
  while(!WindowShouldClose()){ 
    frame_counter++;

    manage_selected_grid(&game_grid);
    //HANDLE INPUT
    if(get_points() >= 50 && !game_grid.selected_block->theres_plant){
      active_peashooter_portraid = 1;
      active_sunflower_portraid = 1;
      if(IsKeyPressed(KEY_J)){
        make_plant(game_grid.selected_block, PEATER);
        decrease_points(50);
      }else if(IsKeyPressed(KEY_K)){
      make_plant(game_grid.selected_block, SUNFLOWER);
      decrease_points(50);
      }
    } else {
      active_peashooter_portraid = 0;
      active_sunflower_portraid = 0;
    }

    if(can_sun_spawn(frame_counter)){
      create_sun(0,0,0); // parametros {0,0} -> sois em lugares aleatórios
     printf("%d\n", frame_counter);
    }
    //UPDATE POSITION
    update_pea(frame_counter);
    update_plant();
    
    BeginDrawing();

      DrawTexturePro(background, (Rectangle){0, 0, 447, 192}, screen_background, (Vector2){0, 0}, 0, WHITE);
      draw_grid();
      draw_outlined_selected_grid(&game_grid);
    
      render_plants(frame_counter);
      render_peas();

      spawn_sun(frame_counter);
      DrawRectangleRounded(left_rect, 0.1, 1, (Color){102, 80, 54, 255});
      points_menu();
      if(get_points() >= 50)
        DrawTextureEx(peashooter_portraid, peashotter_portraid_pos, 0, 3, WHITE);
      else
        DrawTextureEx(peashooter_portraid_desactivated, peashotter_portraid_pos, 0, 3, WHITE);
      if(get_points() >= 50)
        DrawTextureEx(sunflower_portraid, sunflower_portraid_pos, 0, 3, WHITE);
      else
        DrawTextureEx(sunflower_portraid_desactivated, sunflower_portraid_pos, 0, 3, WHITE);
 
    EndDrawing(); 

    collect_sun();
  }
  
  CloseWindow();

  return 0;
}
