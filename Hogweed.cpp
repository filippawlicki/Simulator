#include "CONSTANTS.h"
#include "Hogweed.h"
#include "World.h"
#include "Animal.h"

#include <vector>

Hogweed::Hogweed(World &world, const Point &position) : Plant(world, position, HOGWEED_SYMBOL, HOGWEED_STRENGTH, HOGWEED_COLOR) {}

void Hogweed::Action() {
  std::vector<Point> newPositions = this->world.GetPositionsAround(this->GetPosition());
  for (int i = 0; i < 4; i++) {
    Point new_position = newPositions[i];
    Organism *organism = this->world.GetOrganismAt(new_position);
    if (organism != nullptr) { // Check if there is an animal on the field and it is not a cyber-sheep
      if(dynamic_cast<Animal*>(organism) != nullptr && organism->GetSymbol() != CYBER_SHEEP_SYMBOL) {
        organism->Die();
      }
    }
  }
}

bool Hogweed::Collision(Organism *attackerOrganism) {
  if(attackerOrganism->GetSymbol() == CYBER_SHEEP_SYMBOL) {
    this->Die();
    return false;
  } else {
    attackerOrganism->Die();
    return true;
  }
}

