#pragma once

#include "Plant.h"

class NightshadeBerries : public Plant {
public:
  NightshadeBerries(World &world, const Point &position);
  
  virtual bool Collision(Organism *attacker) override;
  virtual Organism* Clone(const Point &position) override;
};