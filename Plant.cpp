#include "CONSTANTS.h"

#include "Plant.h"

Plant::Plant(World &world, const Point &position, const char &symbol, const int &strength, 
  const double &spreadProbability)
  : Organism(world, position, symbol, strength, PLANTINITIATIVE), 
  spreadProbability(spreadProbability) {}

Plant::~Plant() {}

void Plant::Action() {
  this->TryToSpread();
}

bool Plant::Collision(Organism* attackerOrganism) {
  // Function to make it dead
  return true;
}

double Plant::GetSpreadProbability() const {
  return spreadProbability;
}

