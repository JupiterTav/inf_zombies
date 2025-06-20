#include <raylib.h>
#include <raymath.h>
#include "grid_manager.h"

int main() {

  struct Grid game_grid;
  initialize_grid(&game_grid, 30, 40, 72, 92);
  
  InitWindow(978, 640, "Inf_zombies");

  while(!WindowShouldClose()){ 
    manage_selected_grid(&game_grid);

    BeginDrawing();
    ClearBackground(SKYBLUE); 
    draw_grid(&game_grid);
    draw_outlined_selected_grid(&game_grid);
    if(IsKeyDown(KEY_J) && game_grid.selected_block->theres_plant == -1){
      game_grid.selected_block->theres_plant = 1;
    }

    for(int i = 0; i < GRID_LINES ; i++){
      for(int j = 0; j < GRID_COLUMS; j++){
          if(game_grid.map[i][j].theres_plant == 1)
            DrawCircle(game_grid.map[i][j].tile.x+36, game_grid.map[i][j].tile.y+46, 20, PURPLE);
      }
    }
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}

