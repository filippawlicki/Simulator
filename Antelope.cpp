#include "CONSTANTS.h"
#include "Antelope.h"
#include "World.h"

Antelope::Antelope(World &world, const Point &position) : Animal(world, position, ANTELOPE_SYMBOL, ANTELOPE_STRENGTH, ANTELOPE_INITIATIVE, ANTELOPE_COLOR, ANTELOPE_NAME) {}

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

bool Antelope::Collision(Organism *attackerOrganism) {
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    this->Breed(attackerOrganism);
    return true;
  } else {
    if (rand() % 2 == 0 && dynamic_cast<Animal*>(attackerOrganism) != nullptr) { // 50% chance to escape from the animal
      Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), true, 1);
      if (newPosition != this->GetPosition()) {
        this->world.messageManager.AddAttackRunawayMessage(attackerOrganism->GetName(), this->GetName());
        this->world.MoveOrganism(this, newPosition);
      } else {
        this->Die();
        this->world.messageManager.AddDeathMessage(this->GetName(), attackerOrganism->GetName());
      }
    } else { // Die from plant or failed escape
      this->Die();
      this->world.messageManager.AddDeathMessage(this->GetName(), attackerOrganism->GetName());
    }
    return false;
  }
}