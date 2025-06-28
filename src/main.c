#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include "grid_manager.h"
#include "plant_manager.h"
#include "sun_points_manager.h"

int main() {

  SetTargetFPS(60);
  int frame_counter = 0;
  start_plants();

  struct Grid game_grid;
  initialize_grid(&game_grid, 30, 40, 72, 92);
  start_sun_points();
  
  InitWindow(978, 640, "Inf_zombies");

  while(!WindowShouldClose()){ 
    frame_counter++;
    manage_selected_grid(&game_grid);

    BeginDrawing();
    ClearBackground(SKYBLUE); 
    draw_grid(&game_grid);
    draw_outlined_selected_grid(&game_grid);
    
    if(IsKeyPressed(KEY_J) && !game_grid.selected_block->theres_plant){
      make_plant(game_grid.selected_block, PEATER);
    }
    else if(IsKeyPressed(KEY_K) && !game_grid.selected_block->theres_plant){
      make_plant(game_grid.selected_block, SUNFLOWER);
    }
    on_collision();
    render_plants();
    spawn_sun();
    collect_sun();
    if(can_sun_spawn(frame_counter)){
      create_sun();
     printf("%d\n", frame_counter);
    }
    EndDrawing(); 
  }
  
  CloseWindow();

  return 0;
}
