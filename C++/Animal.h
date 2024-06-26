#pragma once

#include "Organism.h"

class Animal : public Organism {
protected:
  void Breed(Organism* attackerOrganism);
public:
  Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color, const std::string &name);
  ~Animal();

  virtual void Action() override;
  virtual bool Collision(Organism* attackerOrganism) override;
};