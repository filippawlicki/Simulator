#include "Organism.h"

Organism::Organism(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative) :
world(world), position(position), symbol(symbol), strength(strength), initiative(initiative) {}

Point Organism::GetPosition() const {
  return position;
}

void Organism::SetPosition(const int &x, const int &y) {
  position.SetX(x);
  position.SetY(y); 
}

int Organism::GetInitiative() const {
  return initiative;
}

int Organism::GetStrength() const {
  return strength;
}

char Organism::GetSymbol() const {
  return symbol;
}