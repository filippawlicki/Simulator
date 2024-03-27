#include "CONSTANTS.h"
#include "World.h"
#include "GameManager.h"

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
    select = int(getch());
    if(select > 0 && select < 4)
      return select;
  }
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
      break;
    } catch (const std::invalid_argument& e) {
      std::cout << "Invalid Input, Please Try Again." << NEWLINE;
      sleep(2);
      continue;
    }
  }
  sleep(2);
  World& worldInstance = World::getInstance(width, height);
  GameManager gameManager(worldInstance);
  gameManager.PrintTheWorld();
}

void loadGame() {
  std::cout << "LOAD GAME";
}

int main() {
  std::srand(std::time(nullptr));

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