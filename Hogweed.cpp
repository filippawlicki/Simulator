#include "CONSTANTS.h"
#include "Hogweed.h"
#include "World.h"
#include "Animal.h"

#include <vector>

Hogweed::Hogweed(World &world, const Point &position) : Plant(world, position, HOGWEED_SYMBOL, HOGWEED_STRENGTH, HOGWEED_COLOR, HOGWEED_NAME) {}

void Hogweed::Action() {
  if(CanAction()) {
    std::vector<Point> newPositions = this->world.GetPositionsAround(this->GetPosition());
    for (int i = 0; i < 4; i++) {
      Point newPosition = newPositions[i];
      Organism *organism = this->world.GetOrganismAt(newPosition);
      // Check if there is an animal on the field and it is not a cyber-sheep
      if(organism != nullptr && dynamic_cast<Animal*>(organism) != nullptr && organism->GetSymbol() != CYBER_SHEEP_SYMBOL) {
        organism->Die();
        this->world.messageManager.AddDeathMessage(organism->GetName(), this->GetName());
      }
    }
  }
}

bool Hogweed::Collision(Organism *attackerOrganism) {
  this->world.messageManager.AddPlantEatingMessage(this->GetName(), attackerOrganism->GetName());
  this->Die();
  if(attackerOrganism->GetSymbol() != CYBER_SHEEP_SYMBOL) {
    attackerOrganism->Collision(this);
  }
  return false;
}

Organism* Hogweed::Clone(const Point &position) {
  return new Hogweed(this->world, position);
}

