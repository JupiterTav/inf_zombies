{ pkgs ? import <nixpkgs> {}}:
pkgs.stdenv.mkDerivation {
  pname = "inf_zombies";
  version = "v0.01";

  src = ./src;

  buildInputs = [
    pkgs.raylib    
  ];
  buildPhase = ''
    gcc -c grid_manager.c
    gcc -c plant_manager.c
    gcc -c sun_points_manager.c
    gcc -c peashooter.c
    gcc -c main.c 
    gcc -c zombie_manager.c
    gcc -c horde_manager.c
    gcc main.o grid_manager.o plant_manager.o sun_points_manager.o peashooter.o zombie_manager.o horde_manager.o -o inf_zombies -lraylib
    '';
  installPhase = ''
    mkdir -p $out/bin 
    cp inf_zombies $out/bin
    '';
}
