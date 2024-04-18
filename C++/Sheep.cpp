#include "CONSTANTS.h"

#include "Sheep.h"

Sheep::Sheep(World &world, const Point &position) : Animal(world, position, SHEEP_SYMBOL, SHEEP_STRENGTH, SHEEP_INITIATIVE, SHEEP_COLOR, SHEEP_NAME) {}

Organism* Sheep::Clone(const Point &position) {
  return new Sheep(this->world, position);
}

