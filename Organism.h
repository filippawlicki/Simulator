#pragma once

#include "Point.h"
#include <string>

class World;

class Organism {
private:
  char symbol;

  Point position;
  
  int initiative;
  int strength;
  std::string color;

protected:
  World &world;
public:
  Organism(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color);

  virtual void Action() = 0;

  // Returns false if organism frees the field and true if it keeps its place
  virtual bool Collision(Organism *attackerOrganism) = 0;

  void Draw();

  Point GetPosition() const;
  void SetPosition(const int &x, const int &y);

  int GetInitiative() const;
  int GetStrength() const;
  char GetSymbol() const;
  
  virtual Organism* Clone(const Point &position) = 0;
};