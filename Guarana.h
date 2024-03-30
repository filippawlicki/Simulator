#pragma once

#include "Plant.h"

class Guarana : public Plant {
public:
  Guarana(World &world, const Point &position);
  ~Guarana();

  virtual bool Collision(Organism *attacker) override;
  virtual Organism* Clone(const Point &position) override;
};