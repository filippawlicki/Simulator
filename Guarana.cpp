#include "CONSTANTS.h"
#include "Guarana.h"
#include "World.h"

Guarana::Guarana(World &world, const Point &position) : Plant(world, position, GUARANA_SYMBOL, GUARANA_STRENGTH, GUARANA_COLOR, GUARANA_NAME) {}

bool Guarana::Collision(Organism *attacker) {
  attacker->SetStrength(attacker->GetStrength() + 3);
  this->Die();
  this->world.messageManager.AddPlantEatingMessage(this->GetName(), attacker->GetName());
  return false;
}

Organism* Guarana::Clone(const Point &position) {
  return new Guarana(this->world, position);
}