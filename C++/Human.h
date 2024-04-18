#pragma once

#include "Animal.h"

class Human : public Animal {
public:
  Human(World &world, const Point &position);

  virtual void Action() override;
  virtual Organism* Clone(const Point &position) override;

};