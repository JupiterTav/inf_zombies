#include <raylib.h>
#include <raymath.h>
#include <string.h>

#define GRID_COLUMS 9
#define GRID_LINES 5
#define GRID_START 20

typedef struct slice {
  int theres_plant;
  Vector2 center;
  Vector2 dimensions;
}block;

struct Grid{
  Rectangle map[GRID_LINES][GRID_COLUMS];
  Rectangle *selected_block;
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
        grid->map[i][j].x = x + (72 * j);
        grid->map[i][j].y = y + (92*i);
        grid->map[i][j].width  = width ;
        grid->map[i][j].height = height;
      }
    }

    grid->selected_block = &grid->map[0][0];
}

void draw_grid(struct Grid *grid) {
  Color slice_color = GREEN;
  for(int i = 0; i < GRID_LINES; i++){
    for(int j = 0; j < GRID_COLUMS; j++){
      slice_color = ColorIsEqual(slice_color, GREEN) == 1 ? BROWN : GREEN;
      DrawRectangle( grid->map[i][j].x, grid->map[i][j].y,
          grid->map[i][j].width, grid->map[i][j].height, slice_color);
    }
  }
}

void manage_selected_grid(struct Grid *grid){
  if(IsKeyPressed(KEY_RIGHT)){
    if(grid->selected_block != &(grid->map[GRID_LINES - 1][GRID_COLUMS - 1]))
        grid->selected_block++;
    else 
        grid->selected_block = &(grid->map[0][0]);
  }
}

void draw_outlined_selected_grid(struct Grid *grid){
  Rectangle rect;
  //DrawRectangleLines(grid->selected_block->center.x, grid->selected_block->center.y, 
   //   grid->selected_block->dimensions.x, grid->selected_block->dimensions.y, BLACK);
  DrawRectangleLinesEx(*(grid->selected_block), 2, BLACK);
}


