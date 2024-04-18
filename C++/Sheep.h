#pragma once

#include "Animal.h"

class Sheep : public Animal {
public:
  Sheep(World &world, const Point &position);

  virtual Organism* Clone(const Point &position) override;
};