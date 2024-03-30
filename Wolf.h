#pragma once

#include "Animal.h"

class Wolf : public Animal {
public:
  Wolf(World &world, const Point &position);

  virtual Organism* Clone(const Point &position) override;
};