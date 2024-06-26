#include "CONSTANTS.h"
#include "Grass.h"

Grass::Grass(World &world, const Point &position) : Plant(world, position, GRASS_SYMBOL, GRASS_STRENGTH, GRASS_COLOR, GRASS_NAME) {}

Organism* Grass::Clone(const Point &position) {
  return new Grass(this->world, position);
}