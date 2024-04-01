#include "CONSTANTS.h"
#include "CyberSheep.h"

#include "World.h"

CyberSheep::CyberSheep(World &world, const Point &position) : Animal(world, position, CYBER_SHEEP_SYMBOL, CYBER_SHEEP_STRENGTH, CYBER_SHEEP_INITIATIVE, CYBER_SHEEP_COLOR, CYBER_SHEEP_NAME) {}

void CyberSheep::Action() {
  if(CanAction()){
    Point closest = this->world.GetClosestOrganismPosition(this->GetPosition(), HOGWEED_SYMBOL);
    if(closest != this->GetPosition()) {
      Point newPosition;
      if(this->GetPosition().GetX() < closest.GetX()) {
        newPosition = Point(this->GetPosition().GetX() + 1, this->GetPosition().GetY());
      } else if(this->GetPosition().GetX() > closest.GetX()) {
        newPosition = Point(this->GetPosition().GetX() - 1, this->GetPosition().GetY());
      } else if(this->GetPosition().GetY() < closest.GetY()) {
        newPosition = Point(this->GetPosition().GetX(), this->GetPosition().GetY() + 1);
      } else if(this->GetPosition().GetY() > closest.GetY()) {
        newPosition = Point(this->GetPosition().GetX(), this->GetPosition().GetY() - 1);
      }
      Organism* attackerOrganism = this->world.GetOrganismAt(newPosition);
      if (attackerOrganism == nullptr) { // Free space
        this->world.MoveOrganism(this, newPosition);
      } else { // Collision
        attackerOrganism->SetCanAction(false);
        if (this->GetSymbol() == attackerOrganism->GetSymbol()) {
          this->Collision(attackerOrganism); // Breed
        } else {
          if (this->GetStrength() >= attackerOrganism->GetStrength()) {
            bool takenField = attackerOrganism->Collision(this); // Kill
            if(!takenField) {
              this->world.MoveOrganism(this, newPosition);
            }
          } else {
            this->Collision(this); // Killed
          }
        }
      }
    } else {
      Animal::Action();
    }
  }
}

Organism* CyberSheep::Clone(const Point &position) {
  return new CyberSheep(this->world, position);
}