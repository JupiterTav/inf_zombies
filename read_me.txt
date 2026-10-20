Aluno: Wesley Tavares da Silva

Trabalho da cadeira de algoritmos e programação para aplicação dos conceitos estudados ao longo do semestre;

![](assets/banner.png)


executavel: 
nix: 
./results/bin/inf_zombies

cmake: 
    cmake -S . -B build/ (uma vez)        
    cmake --build build/ (para gerar uma nova build)
    ./build/Inf_Zombies

Sem Nix ou Cmake?
    gcc -c grid_manager.c plant_manager.c sun_points_manager.c peashooter.c main.c zombie_manager.c horde_manager.c
    gcc main.o grid_manager.o plant_manager.o sun_points_manager.o peashooter.o zombie_manager.o horde_manager.o -o inf_zombies -lraylib
 
dependencias: 
 raylib

Como jogar?
  Setas(arrow keys) - movimentação pelo grid
  J -> Cria planta ervilha;
  K -> Cria planta sol;
  S -> Coleta sois;

