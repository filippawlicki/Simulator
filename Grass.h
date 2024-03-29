#pragma once

#include "Plant.h"

class Grass : public Plant {
public:
  Grass(World &world, const Point &position);
  ~Grass();

  virtual Organism* Clone(const Point &position) override;
};