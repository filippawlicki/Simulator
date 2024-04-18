#pragma once

#include "Animal.h"

class CyberSheep : public Animal {
public:
  CyberSheep(World &world, const Point &position);

  virtual void Action() override;
  virtual Organism* Clone(const Point &position) override;
};