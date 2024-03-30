#include "CONSTANTS.h"
#include "Guarana.h"

Guarana::Guarana(World &world, const Point &position) : Plant(world, position, GUARANA_SYMBOL, GUARANA_STRENGTH, GUARANA_COLOR) {}
Guarana::~Guarana() {}

bool Guarana::Collision(Organism *attacker) { // TODO
  attacker->SetStrength(attacker->GetStrength() + 3);
  return Plant::Collision(attacker);
}

Organism* Guarana::Clone(const Point &position) {
  return new Guarana(this->world, position);
}