#include "CONSTANTS.h"
#include "Guarana.h"

Guarana::Guarana(World &world, const Point &position) : Plant(world, position, GUARANA_SYMBOL, GUARANA_STRENGTH, GUARANA_COLOR) {}

bool Guarana::Collision(Organism *attacker) {
  attacker->SetStrength(attacker->GetStrength() + 3);
  this->Die();
  return false;
}

Organism* Guarana::Clone(const Point &position) {
  return new Guarana(this->world, position);
}