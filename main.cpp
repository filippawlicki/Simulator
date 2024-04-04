#include "CONSTANTS.h"
#include "World.h"
#include "GameManager.h"

#include "Antelope.h"
#include "Sheep.h"
#include "Turtle.h"
#include "Fox.h"
#include "Grass.h"
#include "SowThistle.h"
#include "Guarana.h"
#include "Wolf.h"
#include "CyberSheep.h"
#include "Hogweed.h"
#include "Human.h"
#include "NightshadeBerries.h"

#include "conio.h"
#include "windows.h"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <unistd.h>

int menu() {
  SetConsoleTitle(TEXT("Filip Pawlicki 198371, OOP Simulation"));
  std::cout << "OOP Simulation" << NEWLINE;
  std::cout << "1) New Game" << NEWLINE;
  std::cout << "2) Load Game" << NEWLINE;
  std::cout << "3) Quit" << NEWLINE;
  std::cout << "Enter Your Choice (Number)" << NEWLINE;
  int select;
  while(true) {
    select = getch() - '0';
    if(select > 0 && select < 4)
      return select;
  }
}

void AddStartingOrganisms(World &world) {
  world.AddOrganism(new Grass(world, world.GetRandomFreePosition()));
  world.AddOrganism(new SowThistle(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Guarana(world, world.GetRandomFreePosition()));
  world.AddOrganism(new NightshadeBerries(world, world.GetRandomFreePosition()));
  world.AddOrganism(new NightshadeBerries(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Hogweed(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Hogweed(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Hogweed(world, world.GetRandomFreePosition()));
  world.AddOrganism(new CyberSheep(world, world.GetRandomFreePosition()));
  world.AddOrganism(new CyberSheep(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Wolf(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Turtle(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Turtle(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Fox(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Fox(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Sheep(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Sheep(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Antelope(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Antelope(world, world.GetRandomFreePosition()));
  world.AddOrganism(new Human(world, world.GetRandomFreePosition()));
}

void newGame() {
  system("cls");
  int width, height;
  std::string widthString, heightString;

  while(true) {
    std::cout << "Enter the Width of Your Game: " << NEWLINE;
    std::cin >> widthString;
    std::cout << "Enter the Height of Your Game: " << NEWLINE;
    std::cin >> heightString;

    try {
      width = std::stoi(widthString);
      height = std::stoi(heightString);
      if(width * height < 21) {
        std::cout << "The Board is Too Small, Please Try Again." << NEWLINE;
        continue;
      }
      break;
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid Input, Please Try Again." << NEWLINE;
      sleep(2);
      continue;
    }
  }
  sleep(2);
  World& worldInstance = World::GetInstance(width, height);
  GameManager gameManager(worldInstance);
  AddStartingOrganisms(worldInstance);
  gameManager.GameLoop();
}

void loadGame() {
  std::cout << "LOAD GAME";
}

int main() {
  std::srand(std::time(nullptr));
  system("cls");
  int option = menu();
  switch(option) {
    case 1:
      newGame();
      break;
    case 2:
      loadGame();
      break;
    case 3:
      exit(0);
  }
  return 0;
}