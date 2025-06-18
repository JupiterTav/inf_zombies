#include <raylib.h>
#include <raymath.h>

#define GRID_COLUMS 9
#define GRID_LINES 5
#define GRID_START 20

typedef struct Block {
  int theres_plant;
  Rectangle tile;
}Slice;

struct Grid{
  Slice map[GRID_LINES][GRID_COLUMS];
  Slice *selected_block;
};

void initialize_grid(struct Grid *grid, float x, float y, float width, float height);
void draw_grid(struct Grid *grid);
void draw_outlined_selected_grid(struct Grid *grid);
void manage_selected_grid(struct Grid *grid);

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

void initialize_grid(struct Grid *grid, float x, float y, float width, float height){
    for(int i = 0; i < GRID_LINES; i++) {
      for(int j = 0; j < GRID_COLUMS; j++){
        grid->map[i][j].tile.x = x + (72 * j);
        grid->map[i][j].tile.y = y + (92*i);
        grid->map[i][j].tile.width  = width ;
        grid->map[i][j].tile.height = height;
      }
    }

    grid->selected_block = &grid->map[0][0];
}

void draw_grid(struct Grid *grid) {
  Color slice_color = GREEN;
  for(int i = 0; i < GRID_LINES; i++){
    for(int j = 0; j < GRID_COLUMS; j++){
      slice_color = ColorIsEqual(slice_color, GREEN) == 1 ? BROWN : GREEN;
      DrawRectangle( grid->map[i][j].tile.x, grid->map[i][j].tile.y,
          grid->map[i][j].tile.width, grid->map[i][j].tile.height, slice_color);
    }
  }
}

void manage_selected_grid(struct Grid *grid){
 
 Slice *last_block = &grid->map[GRID_LINES - 1][GRID_COLUMS - 1];

  if(IsKeyPressed(KEY_RIGHT)){
    grid->selected_block = (grid->selected_block != (last_block))
      ? grid->selected_block + 1 : &(grid->map[0][0]);
    }

  else if(IsKeyPressed(KEY_LEFT)){
    grid->selected_block = (grid->selected_block != &(grid->map[0][0])) 
      ? grid->selected_block - 1 : last_block;
  }
  
  else if(IsKeyPressed(KEY_DOWN)){      
    grid->selected_block += ( grid->selected_block >= &(grid->map[GRID_LINES - 1][0]) && 
                              grid->selected_block <= (last_block)) 
      ? -36 : 9;
  }
  else if(IsKeyPressed(KEY_UP)){
    grid->selected_block += ( grid->selected_block >= &(grid->map[0][0]) && 
                              grid->selected_block<=&(grid->map[0][GRID_COLUMS-1])) 
      ? 36 : -9;
  }

}
void draw_outlined_selected_grid(struct Grid *grid){
  DrawRectangleLinesEx((grid->selected_block->tile), 5, BLACK);
}


