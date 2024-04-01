#include "CONSTANTS.h"
#include "GameManager.h"

#include <iostream>
#include <cstdlib>
#include "conio.h"
#include <unistd.h>

GameManager::GameManager(World &world) : world(world), quit(false) {}

GameManager::~GameManager() {}

bool GameManager::Quit() const {
  return quit;
}

void GameManager::PrintTheWorld() {
  system("cls");
  int height = world.GetHeight();
  int width = world.GetWidth();
  Organism ***worldMap = world.GetMapOfTheWorld();
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
  for (int y = 0; y < height; y++) {
    std::cout << "|";
    for (int x = 0; x < width; x++)
    {
      if (worldMap[x][y] != nullptr) {
        worldMap[x][y]->Draw();
      }
      else {
        std::cout << " ";
      }
    }
    std::cout << "|" << NEWLINE;
  }
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
  world.messageManager.PrintMessages();
}

char GameManager::GetPlayerInput() {
  int input;
  do {
    input = getch();
    if (input == 224) {
      input = getch(); // Read the extended key code
      switch (input) {
        case 72: // Up arrow key
          input = 'U';
          break;
        case 80: // Down arrow key
          input = 'D';
          break;
        case 75: // Left arrow key
          input = 'L';
          break;
        case 77: // Right arrow key
          input = 'R';
          break;
      }
    } else if (input == 120) {
      return 'x';
    }
  } while (input != 'U' && input != 'D' && input != 'L' && input != 'R');
  return char(input);
}

void GameManager::GameLoop() {
  quit = false;
  while (!quit) {
    PrintTheWorld();
    char input = GetPlayerInput();
    if(input == 'x') {
      quit = true;
      break;
    }
    world.MakeTurn();
    // PrintMessages();
  }
}