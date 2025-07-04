#include "horde_manager.h"
#include "stdio.h"
#include "zombie_manager.h"

int horde_zombies[3];
int enemies_to_spawn;
int current_horde = 0;

HORDE_STATES horde_state = STARTING;

void initialize_horde();

void initialize_horde(){
  FILE *config;
  if(!(config = fopen("data/config.txt", "r"))){
    printf("Erro na leitura do arquivo das hordas");
  } else {
    fscanf(config, "%d %d %d", &horde_zombies[0], &horde_zombies[1], &horde_zombies[2]);
    printf("INIMIGOS POR HORDA: '%d %d %d", horde_zombies[0], horde_zombies[1], horde_zombies[2]);
  }
}

void handle_horde(int frame_counter){
  switch(horde_state){
  case STARTING:
    enemies_to_spawn = horde_zombies[current_horde];
    current_horde++;
    horde_state = RUNNING;
  break;
  case RUNNING:
      if((frame_counter % 240 == 0) && enemies_to_spawn > 0){
        create_zombie();
        enemies_to_spawn--;
      }
      if(is_all_dead() && enemies_to_spawn <= 0){
        horde_state = (current_horde > 3) ? FINISHED : STARTING;
      }
  break;
  case FINISHED:
    break;
  }
}

int all_clean(){
  return horde_state == FINISHED;
}
