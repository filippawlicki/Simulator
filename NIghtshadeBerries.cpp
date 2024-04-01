#include "CONSTANTS.h"
#include "NightshadeBerries.h"

NightshadeBerries::NightshadeBerries(World &world, const Point &position) : Plant(world, position, NIGHTSHADE_BERRIES_SYMBOL, NIGHTSHADE_BERRIES_STRENGTH, NIGHTSHADE_BERRIES_COLOR) {}

bool NightshadeBerries::Collision(Organism *attacker) {
  attacker->Die();
  this->Die();
  return false;
}

Organism* NightshadeBerries::Clone(const Point &position) {
  return new NightshadeBerries(this->world, position);
}