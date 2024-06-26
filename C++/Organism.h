#pragma once

#include "Point.h"
#include <string>

class World;

class Organism {
private:
  char symbol;

  Point position;
  
  bool canAction;

  int age;
  int initiative;
  int strength;
  std::string color;
  std::string name;

protected:
  World &world;
public:
  Organism(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color, const std::string &name);

  virtual void Action() = 0;

  // Returns false if organism frees the field and true if it keeps its place
  virtual bool Collision(Organism *attackerOrganism) = 0;

  void Draw();

  void Die();

  Point GetPosition() const;
  void SetPosition(const int &x, const int &y);

  int GetAge() const;
  void IncrementAge();

  bool CanAction() const;
  void SetCanAction(const bool &canAction);

  int GetInitiative() const;

  int GetStrength() const;
  void SetStrength(const int &strength);

  std::string GetName() const;

  char GetSymbol() const;
  
  virtual Organism* Clone(const Point &position) = 0;
};