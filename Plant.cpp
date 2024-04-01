#include "CONSTANTS.h"

#include "World.h"
#include "Plant.h"
#include <stdlib.h>

Plant::Plant(World &world, const Point &position, const char &symbol, const int &strength, const std::string &color)
  : Organism(world, position, symbol, strength, PLANT_INITIATIVE, color), 
  spreadProbability(SPREAD_PROBABILITY) {}

Plant::~Plant() {}

void Plant::Action() {
  if(CanAction()){
    this->TryToSpread();
  }
}

bool Plant::Collision(Organism* attackerOrganism) {
  this->Die();
  return false;
}

double Plant::GetSpreadProbability() const {
  return spreadProbability;
}

void Plant::TryToSpread() {
  if (rand() % 100 < spreadProbability * 100) {
    Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), true, 1);
    if (newPosition != this->GetPosition()) {
      Organism* newPlant = this->Clone(newPosition);
      this->world.AddOrganism(newPlant);
    }
  }
}

