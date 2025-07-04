#include "grid_manager.h"

#include <raylib.h>
#include <raymath.h>

#define GRID_COLUMS 9
#define GRID_LINES 5


Texture2D grid_texture;
void initialize_grid(struct Grid *grid, float x, float y, float width, float height){
  grid_texture = LoadTexture("assets/sprites/grid.png");
  for(int i = 0; i < GRID_LINES; i++) {
      for(int j = 0; j < GRID_COLUMS; j++){
        grid->map[i][j].tile.x = x + (width * j);
        grid->map[i][j].tile.y = y + (height*i);
        grid->map[i][j].tile.width  = width ;
        grid->map[i][j].tile.height = height;
        grid->map[i][j].theres_plant = 0;
      }
    }

    grid->selected_block = &grid->map[0][0];
}

void draw_grid() {
  DrawTexturePro(grid_texture, (Rectangle){0, 0, 246, 169}, (Rectangle){50, 143, 648, 480}, (Vector2){0, 0}, 0, WHITE); //textura, source, posicao, posicao relativa ao source
}

void manage_selected_grid(struct Grid *grid){
 
  Block *last_block = &grid->map[GRID_LINES - 1][GRID_COLUMS - 1];

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
  DrawRectangleLinesEx((grid->selected_block->tile), 3, BLACK);
}
