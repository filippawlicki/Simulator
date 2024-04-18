#include "CONSTANTS.h"
#include "GameManager.h"

#include <fstream>
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
  // Info
  std::cout << "Q - Quit, S - Save Game, Space - Make Turn" << NEWLINE;
  std::cout << "Arrows - Move Human";
  if(world.GetHumanInput() == 'U') {
    std::cout << " (Your Move - Up), ";
  } else if(world.GetHumanInput() == 'D') {
    std::cout << " (Your Move - Down), ";
  } else if(world.GetHumanInput() == 'L') {
    std::cout << " (Your Move - Left), ";
  } else if(world.GetHumanInput() == 'R') {
    std::cout << " (Your Move - Right), ";
  } else {
    std::cout << ", ";
  }
  std::cout << "X - Super Power";
  if(world.GetHumanSuperPowerDuration() > 0) {
    std::cout << " (Active - " << world.GetHumanSuperPowerDuration() << " Turns Left)";
  } else if (world.GetHumanSuperPowerCooldown() == 0) {
    std::cout << " (Ready)";
  } else {
    std::cout << " (Inactive - " << world.GetHumanSuperPowerCooldown() << " Turns Left)";
  }
  std::cout << NEWLINE;
  // Board
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
  // Messages
  world.messageManager.PrintMessages();
}

char GameManager::GetPlayerInput() {
  while (kbhit()) { // Clear the buffer
    getch();
  }
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
    }
  } while (input != 'U' && input != 'D' && input != 'L' && input != 'R' && input != 'x' && input != 'q' && input != 's' && input != 32);
  return char(input);
}

void GameManager::ExecutePlayerInput() {
  char input;
  bool print = true, legalMove = false, makeTurn = false;
  while(!makeTurn && !quit && (world.GetHumanInput() != 'U' || world.GetHumanInput() != 'D' || world.GetHumanInput() != 'L' || world.GetHumanInput() != 'R')){
    if(print)
      PrintTheWorld();
    input = GetPlayerInput();
    if(input == 'q') { // Quit
      quit = true;
    } else if(input == 's') { // Save game
      std::string fileName;
      std::cout << "Enter the name of the file to save: ";
      std::cin >> fileName;
      std::ofstream saveFile(SAVE_DIR + fileName + ".txt");
      if (saveFile.is_open()) {
        // Save world state
        saveFile << world.GetHeight() << " " << world.GetWidth() << "\n";
        saveFile << world.GetOrganisms().size() << "\n"; // Count of organisms
        Organism ***worldMap = world.GetMapOfTheWorld();
        for (int y = 0; y < world.GetHeight(); y++) {
          for (int x = 0; x < world.GetWidth(); x++) {
            if (worldMap[x][y] != nullptr) {
              saveFile << x << " " << y << " " << worldMap[x][y]->GetSymbol() << " " << worldMap[x][y]->GetStrength() << "\n";
              if (worldMap[x][y]->GetSymbol() == HUMAN_SYMBOL) { // Save player state
                saveFile << world.GetHumanSuperPowerCooldown() << world.GetHumanSuperPowerDuration() << "\n";
              }
            }
          }
        }
        saveFile.close();
        std::cout << "Game saved successfully" << NEWLINE;
      } else {
        std::cout << "Failed to save the game" << NEWLINE;
      }
      print = false;
    } else if(input == 'x') { // Super Power
      if(world.GetHumanSuperPowerCooldown() == 0) {
        world.SetHumanSuperPowerDuration(HUMAN_SUPER_POWER_DURATION);
        world.SetHumanSuperPowerCooldown(HUMAN_SUPER_POWER_COOLDOWN);
        print = true;
      }
    } else if(input == 'U' || input == 'D' || input == 'L' || input == 'R') { // Arrows
      if(world.IsHumanMoveLegal(input)) {
        world.SetHumanInput(input);
        legalMove = true;
        print = true;
      } else {
        std::cout << "Illegal Move" << NEWLINE;
        legalMove = false;
        print = false;
      }
    } else if (input == 32) { // Make Turn
      if(legalMove) {
        makeTurn = true;
      }
    } else {
      print = false;
    }
  }
}

void GameManager::GameLoop() {
  quit = false;
  while (!quit && !world.IsHumanDead()) {
    world.SetHumanInput(' '); // No move
    ExecutePlayerInput();
    if(!quit)
      world.MakeTurn();
  }
  PrintTheWorld();
  if(quit) {
    std::cout << "You quit the game" << NEWLINE;
  } else {
    std::cout << "Game Over, You died" << NEWLINE;
  }
  std::cout << "Press any key to continue..." << NEWLINE;
  getch();
}