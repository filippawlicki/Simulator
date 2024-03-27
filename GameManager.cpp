#include "CONSTANTS.h"
#include "GameManager.h"

#include <iostream>
#include <cstdlib>

GameManager::GameManager(World &world) : world(world), quit(false) {}

GameManager::~GameManager() {}

bool GameManager::Quit() const {
  return quit;
}

void GameManager::PrintTheWorld() {
  system("cls");
  int height = world.GetHeight();
  int width =  world.GetWidth();
  Organism*** worldMap = world.getMapOfTheWorld();
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
  for(int x = 0; x < width; x++) {
    std::cout << "|";
    for(int y = 0; y < height; y++) {
      if(worldMap[x][y] != nullptr) {
        worldMap[x][y]->Draw();
      } else {
        std::cout << " ";
      }
    }
    std::cout << "|";
  }
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
}