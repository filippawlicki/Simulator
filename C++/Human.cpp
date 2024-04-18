#include "CONSTANTS.h"
#include "Human.h"

#include "World.h"

Human::Human(World &world, const Point &position) : Animal(world, position, HUMAN_SYMBOL, HUMAN_STRENGTH, HUMAN_INITIATIVE, HUMAN_COLOR, HUMAN_NAME) {}

void Human::Action() {
  char input = this->world.GetHumanInput();
  if(CanAction()) {
    Point newPosition;
    switch(input) {
      case 'D':
        newPosition = Point(this->GetPosition().GetX(), this->GetPosition().GetY() + 1);
        break;
      case 'U':
        newPosition = Point(this->GetPosition().GetX(), this->GetPosition().GetY() - 1);
        break;
      case 'L':
        newPosition = Point(this->GetPosition().GetX() - 1, this->GetPosition().GetY());
        break;
      case 'R':
        newPosition = Point(this->GetPosition().GetX() + 1, this->GetPosition().GetY());
        break;
      default:
        break;
    }
    Organism* attackerOrganism = this->world.GetOrganismAt(newPosition);
    if (attackerOrganism == nullptr) { // Free space
      this->world.MoveOrganism(this, newPosition);
    } else { // Collision
      attackerOrganism->SetCanAction(false);
      if (this->GetStrength() >= attackerOrganism->GetStrength()) {
        bool takenField = attackerOrganism->Collision(this); // Kill
        if(!takenField && attackerOrganism->GetSymbol() != HOGWEED_SYMBOL && attackerOrganism->GetSymbol() != NIGHTSHADE_BERRIES_SYMBOL){
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

Organism* Human::Clone(const Point &position) {
  return new Human(this->world, position);
}