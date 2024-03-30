#include "CONSTANTS.h"
#include "SowThistle.h"

SowThistle::SowThistle(World &world, const Point &position) : Plant(world, position, SOWTHISTLE_SYMBOL, SOWTHISTLE_STRENGTH, SOWTHISTLE_COLOR) {}

void SowThistle::Action() {
  for (int i = 0; i < 3; i++) {
    Plant::Action();
  }
}

Organism* SowThistle::Clone(const Point &position) {
  return new SowThistle(this->world, position);
}