#include <raylib.h>
#include <raymath.h>
#include "grid_manager.h"

#define GRID_COLUMS 9
#define GRID_LINES 5
#define GRID_START 20

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
    EndDrawing();
  }
  
  CloseWindow();

  return 0;
}

