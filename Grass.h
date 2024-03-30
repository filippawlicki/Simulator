#pragma once

#include "Plant.h"

class Grass : public Plant {
public:
  Grass(World &world, const Point &position);

  virtual Organism* Clone(const Point &position) override;
};