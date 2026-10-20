#ifndef GRID_MANAGER_H
#define GRID_MANAGER_H
#include "raylib.h"

#define GRID_COLUMS 9
#define GRID_LINES 5
#define GRID_START 20


typedef struct{
  int theres_plant;
  Rectangle tile;
  Texture2D block_texture;
}Block;

struct Grid{
  Block map[GRID_LINES][GRID_COLUMS];
  Block *selected_block;
};


void initialize_grid(struct Grid *grid, float x, float y, float width, float height);
void draw_grid();
void draw_outlined_selected_grid(struct Grid *grid);
void manage_selected_grid(struct Grid *grid);



#endif // !GRID_MANAGER

