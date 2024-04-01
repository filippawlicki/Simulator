#include "CONSTANTS.h"
#include "Antelope.h"
#include "World.h"

Antelope::Antelope(World &world, const Point &position) : Animal(world, position, ANTELOPE_SYMBOL, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, ANTELOPE_COLOR) {}

Organism* Antelope::Clone(const Point &position) {
  return new Antelope(this->world, position);
}

void Antelope::Action() {
  if(CanAction()){
    Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false, 2);
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
            if(!takenField) {
              this->world.MoveOrganism(this, newPosition);
            }
          } else {
            this->Collision(this); // Killed
          }
        }
      }
    }
  }
}

bool Antelope::Collision(Organism *attackerOrganism) {
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    this->Breed(attackerOrganism->GetPosition());
    return true;
  } else {
    if (rand() % 2 == 0) {
      Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), true, 1);
      if (newPosition != this->GetPosition()) {
        this->world.MoveOrganism(this, newPosition);
      } else {
        this->Die();
      }
    }
    return false;
  }
}