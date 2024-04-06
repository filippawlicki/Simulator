#include "CONSTANTS.h"
#include "World.h"
#include "Animal.h"

Animal::Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color, const std::string &name)
  : Organism(world, position, symbol, strength, initiative, color, name) {}

Animal::~Animal() {}

void Animal::Action() {
  if(CanAction()){
    Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false, 1);
    if (newPosition != this->GetPosition()) {
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

bool Animal::Collision(Organism* attackerOrganism) {
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    this->Breed(attackerOrganism);
    return true;
  } else {
    this->Die();
    this->world.messageManager.AddDeathMessage(this->GetName(), attackerOrganism->GetName());
    return false;
  }
}

void Animal::Breed(Organism* attackerOrganism) {
  Point newPosition = this->world.GetRandomPositionForChild(this->GetPosition(), attackerOrganism->GetPosition());
  if (newPosition != this->GetPosition()) {
    Organism* newOrganism = this->Clone(newPosition);
    this->world.messageManager.AddReproductionMessage(this->GetName(), attackerOrganism->GetName(), newOrganism->GetName());
    this->world.AddOrganism(newOrganism);
  }
}