#include "CONSTANTS.h"
#include "NightshadeBerries.h"

#include "World.h"

NightshadeBerries::NightshadeBerries(World &world, const Point &position) : Plant(world, position, NIGHTSHADE_BERRIES_SYMBOL, NIGHTSHADE_BERRIES_STRENGTH, NIGHTSHADE_BERRIES_COLOR, NIGHTSHADE_BERRIES_NAME) {}

bool NightshadeBerries::Collision(Organism *attacker) {
  this->world.messageManager.AddPlantEatingMessage(this->GetName(), attacker->GetName());
  this->Die();
  attacker->Collision(this);
  return false;
}

Organism* NightshadeBerries::Clone(const Point &position) {
  return new NightshadeBerries(this->world, position);
}