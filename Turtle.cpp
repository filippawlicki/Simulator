#include "CONSTANTS.h"
#include "Turtle.h"

#include "World.h"

Turtle::Turtle(World &world, const Point &position) : Animal(world, position, TURTLE_SYMBOL, TURTLE_STRENGTH, TURTLE_INITIATIVE, TURTLE_COLOR, TURTLE_NAME) {}

Organism* Turtle::Clone(const Point &position) {
  return new Turtle(this->world, position);
}

void Turtle::Action() {
  if(CanAction()){
    if (rand() % 4 == 0) {
      Animal::Action();
    }
  }
}

bool Turtle::Collision(Organism *attackerOrganism) {
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    this->Breed(attackerOrganism);
    return true;
  } 
  if(attackerOrganism->GetStrength() < 5) {
    this->world.messageManager.AddAttackRepellMessage(attackerOrganism->GetName(), this->GetName());
    return true;
  } else {
    return Animal::Collision(attackerOrganism);
  }
}