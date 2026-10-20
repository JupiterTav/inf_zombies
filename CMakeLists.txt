cmake_minimum_required(VERSION 4.0)

project(Inf_Zombies C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(raylib)

add_executable(Inf_Zombies
   src/main.c
   src/peashooter.c
   src/horde_manager.c
   src/grid_manager.c
   src/zombie_manager.c
   src/sun_points_manager.c
   src/plant_manager.c
)

include_directories(${src/include})

target_link_libraries(Inf_Zombies PRIVATE raylib)
