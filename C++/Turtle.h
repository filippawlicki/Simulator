#pragma once

#include "Animal.h"

class Turtle : public Animal {
public:
  Turtle(World &world, const Point &position);

  virtual void Action() override;
  virtual bool Collision(Organism *attackerOrganism) override;
  virtual Organism* Clone(const Point &position) override;
};