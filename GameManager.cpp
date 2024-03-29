#include "CONSTANTS.h"
#include "GameManager.h"

#include <iostream>
#include <cstdlib>
#include "conio.h"

GameManager::GameManager(World &world) : world(world), quit(false) {}

GameManager::~GameManager() {}

bool GameManager::Quit() const
{
  return quit;
}

void GameManager::PrintTheWorld()
{
  system("cls");
  int height = world.GetHeight();
  int width = world.GetWidth();
  Organism ***worldMap = world.GetMapOfTheWorld();
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
  for (int y = 0; y < height; y++)
  {
    std::cout << "|";
    for (int x = 0; x < width; x++)
    {
      if (worldMap[x][y] != nullptr)
      {
        worldMap[x][y]->Draw();
      }
      else
      {
        std::cout << " ";
      }
    }
    std::cout << "|" << NEWLINE;
  }
  std::cout << "+" << std::string(width, '-') << "+" << NEWLINE;
}

char GameManager::GetPlayerInput()
{
  char input;
  do
  {
    input = getch();
    if (input == '\033') { // First value for arrow keys
      getch(); // Skip [
      switch (getch()) {
      case 'A': // UP
        input = '1';
        break;
      case 'B': // DOWN
        input = '2';
        break;
      case 'C': // RIGHT
        input = '3';
        break;
      case 'D': // LEFT
        input = '4';
        break;
      }
    }
  } while (input != '1' && input != '2' && input != '3' && input != '4' && input != 'x');
  return input;
}

void GameManager::GameLoop()
{
  quit = false;
  while (!quit)
  {
    PrintTheWorld();
    GetPlayerInput();
    world.MakeTurn();
    // PrintMessages();
  }
}