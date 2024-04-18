#pragma once

#include "Animal.h"

class Fox : public Animal {
public:
  Fox(World &world, const Point &position);

  virtual void Action() override;
  virtual Organism* Clone(const Point &position) override;
};