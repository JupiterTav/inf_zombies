#include <raylib.h>
#include <raymath.h>

#define GRID_COLUMS 9
#define GRID_LINES 5
#define GRID_START 20

typedef struct slice {
  int theres_plant;
  Vector2 center;
  Vector2 dimensions;
}block;

struct Grid{
  block map[GRID_LINES][GRID_COLUMS];
  block *selected_block;
};

void initialize_grid(struct Grid *grid, float x, float y, float width, float height);
void draw_grid(struct Grid *grid);

int main() {
  struct Grid game_grid;
  initialize_grid(&game_grid, 30, 40, 72, 92);
  
  InitWindow(978, 640, "Inf_zombies");

  while(!WindowShouldClose()){ 
    draw_grid(&game_grid);
  }
  CloseWindow();
  return 0;
}

void initialize_grid(struct Grid *grid, float x, float y, float width, float height){
    for(int i = 0; i < GRID_LINES; i++) {
      for(int j = 0; j < GRID_COLUMS; j++){
      grid->map[i][j].center.x = x;
      grid->map[i][j].center.y = y;
      grid->map[i][j].dimensions.x  = width ;
      grid->map[i][j].dimensions.y = height;
    }
  }
}

void draw_grid(struct Grid *grid) {
  BeginDrawing();
  Color slice_color = GREEN;
  for(int i = 0; i < GRID_LINES; i++){
    for(int j = 0; j < GRID_COLUMS; j++){
      slice_color = ColorIsEqual(slice_color, GREEN) == 1 ? DARKBROWN : GREEN;
      DrawRectangle( grid->map[i][j].center.x + (72*j), grid->map[i][j].center.y + (92*i),
          grid->map[i][j].dimensions.x, grid->map[i][j].dimensions.y, slice_color);
    }
  }
  EndDrawing();
}


