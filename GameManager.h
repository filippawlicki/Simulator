#pragma once

#include "World.h"

class GameManager {
private:
  World &world;
  bool quit;
  
  //void PrintTheWorld();
  void PrintMessages();
  char GetPlayerInput();
public:
  GameManager(World &world);
  ~GameManager();

  bool Quit() const;
  void PrintTheWorld(); // CHWILOWO POTEM MUSI BYC PRIVATE
  void GameLoop();
};  