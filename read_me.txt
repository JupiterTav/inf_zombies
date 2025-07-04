Aluno: Wesley Tavares da Silva Cartão 00602430

Trabalho da cadeira de algoritmos e programação para aplicação dos conceitos estudados ao longo do semestre;

executavel: ./results/bin/inf_zombies;
dependencias para compiação: raylib

###Como compilar?
    gcc -c grid_manager.c plant_manager.c sun_points_manager.c peashooter.c main.c zombie_manager.c horde_manager.c
    gcc main.o grid_manager.o plant_manager.o sun_points_manager.o peashooter.o zombie_manager.o horde_manager.o -o inf_zombies -lraylib
 
###Como jogar?
  Setas(arrow keys) - movimentação pelo grid
  J -> Cria planta ervilha;
  K -> Cria planta sol;
  S -> Coleta sois;

