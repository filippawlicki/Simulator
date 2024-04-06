#include "CONSTANTS.h"
#include "Fox.h"
#include "World.h"

#include <vector>

Fox::Fox(World &world, const Point &position) : Animal(world, position, FOX_SYMBOL, FOX_STRENGTH, FOX_INITIATIVE, FOX_COLOR, FOX_NAME) {}

Organism* Fox::Clone(const Point &position) {
  return new Fox(this->world, position);
}

void Fox::Action() {
  if(CanAction()) {
    std::vector<Point> possibleMoves = this->world.GetPositionsAround(this->GetPosition());
    Point newPosition = this->GetPosition();
    for(auto &move : possibleMoves) {
      if(this->world.GetOrganismAt(move) == nullptr || this->world.GetOrganismAt(move)->GetStrength() <= this->GetStrength()) {
        newPosition = move;
        break;
      }
    }
    if(newPosition != this->GetPosition()) {
      Organism* attackerOrganism = this->world.GetOrganismAt(newPosition);
      if(attackerOrganism == nullptr) { // Free space
        this->world.MoveOrganism(this, newPosition);
      } else { // Collision
        attackerOrganism->SetCanAction(false);
        if(this->GetSymbol() == attackerOrganism->GetSymbol()) {
          this->Collision(attackerOrganism); // Breed
        } else {
          if(this->GetStrength() >= attackerOrganism->GetStrength()) {
            bool takenField = attackerOrganism->Collision(this); // Kill
            if(!takenField && attackerOrganism->GetSymbol() != HOGWEED_SYMBOL && attackerOrganism->GetSymbol() != NIGHTSHADE_BERRIES_SYMBOL) {
              this->world.MoveOrganism(this, newPosition);
            }
          } else {
            if(attackerOrganism->GetSymbol() == HOGWEED_SYMBOL || attackerOrganism->GetSymbol() == NIGHTSHADE_BERRIES_SYMBOL) { // Hogweed and NightshadeBerries kill the attacker, but they're also eaten
              attackerOrganism->Collision(this);
            } else {
              this->Collision(attackerOrganism); // Killed
            }
          }
        }
      }
    }
  }
}