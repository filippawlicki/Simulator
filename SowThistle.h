#pragma once

#include "Plant.h"

class SowThistle : public Plant {
public:
  SowThistle(World &world, const Point &position);
  ~SowThistle();


  virtual void Action() override;
  virtual Organism* Clone(const Point &position) override;
};