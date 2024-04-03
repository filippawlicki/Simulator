#pragma once

#include "Plant.h"

class Hogweed : public Plant {
public:
  Hogweed(World &world, const Point &position);
  
  virtual void Action() override;
  virtual bool Collision(Organism *attackerOrganism) override;
  virtual Organism* Clone(const Point &position) override;
};