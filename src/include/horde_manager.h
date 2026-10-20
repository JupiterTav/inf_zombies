#ifndef HORDE_MANAGER_H
#define HORDE_MANAGER_H

typedef enum{
  STARTING,
  RUNNING,
  FINISHED,
}HORDE_STATES;


void initialize_horde();
void handle_horde(int frame_counter);
int all_clean();

#endif
