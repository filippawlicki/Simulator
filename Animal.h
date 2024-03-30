#pragma once

#include "Organism.h"

class Animal : public Organism {
private:
  void Breed(const Point &attackerPosition);
public:
  Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color);
  ~Animal();

  virtual void Action() override;
  virtual bool Collision(Organism* attackerOrganism) override;
};