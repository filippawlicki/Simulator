#include "CONSTANTS.h"

#include "Wolf.h"

Wolf::Wolf(World &world, const Point &position) : Animal(world, position, WOLF_SYMBOL, WOLF_STRENGTH, WOLF_INITIATIVE, WOLF_COLOR, WOLF_NAME) {}

Organism* Wolf::Clone(const Point &position) {
  return new Wolf(this->world, position);
}