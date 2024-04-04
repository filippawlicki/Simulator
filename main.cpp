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

#include <fstream>
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
  std::cout << "Enter the name of the save file: " << NEWLINE;
  std::string fileName;
  std::cin >> fileName;
  fileName = "SAVES/" + fileName + ".txt"; // Add the directory path

  std::ifstream file(fileName);
  if (!file.is_open()) {
    std::cout << "Failed to open the save file." << NEWLINE;
    return;
  }

  // Read the game state from the file and initialize the world and game manager
  int width, height;
  file >> width >> height;
  World& worldInstance = World::GetInstance(width, height);
  GameManager gameManager(worldInstance);

  // Read and add organisms to the world
  int organismCount;
  file >> organismCount;
  for (int i = 0; i < organismCount; i++) {
    std::string organismType;
    int x, y, strength;
    file >> x >> y >> organismType >> strength;
    // Create the organism based on its type and add it to the world
    Organism* organism;
    if (organismType[0] == GRASS_SYMBOL) {
      organism = new Grass(worldInstance, Point(x, y));
    } else if (organismType[0] == SOWTHISTLE_SYMBOL) {
      organism = new SowThistle(worldInstance, Point(x, y));
    } else if (organismType[0] == GUARANA_SYMBOL) {
      organism = new Guarana(worldInstance, Point(x, y));
    } else if (organismType[0] == NIGHTSHADE_BERRIES_SYMBOL) {
      organism = new NightshadeBerries(worldInstance, Point(x, y));
    } else if (organismType[0] == HOGWEED_SYMBOL) {
      organism = new Hogweed(worldInstance, Point(x, y));
    } else if (organismType[0] == CYBER_SHEEP_SYMBOL) {
      organism = new CyberSheep(worldInstance, Point(x, y));
    } else if (organismType[0] == WOLF_SYMBOL) {
      organism = new Wolf(worldInstance, Point(x, y));
    } else if (organismType[0] == TURTLE_SYMBOL) {
      organism = new Turtle(worldInstance, Point(x, y));
    } else if (organismType[0] == FOX_SYMBOL) {
      organism = new Fox(worldInstance, Point(x, y));
    } else if (organismType[0] == SHEEP_SYMBOL) {
      organism = new Sheep(worldInstance, Point(x, y));
    } else if (organismType[0] == ANTELOPE_SYMBOL) {
      organism = new Antelope(worldInstance, Point(x, y));
    } else if (organismType[0] == HUMAN_SYMBOL) {
      organism = new Human(worldInstance, Point(x, y));
      int superPowerCooldown;
      file >> superPowerCooldown;
      worldInstance.SetHumanSuperPowerCooldown(superPowerCooldown);
      int superPowerDuration;
      file >> superPowerDuration;
      worldInstance.SetHumanSuperPowerDuration(superPowerDuration);
    }
    organism->SetStrength(strength);
    worldInstance.AddOrganism(organism);
  }

  // Close the file
  file.close();
  // Start the game loop
  gameManager.GameLoop();
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