#include "World.h"
#include "Animal.h"

Animal::  Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color)
  : Organism(world, position, symbol, strength, initiative, color) {}

Animal::~Animal() {}

void Animal::Action() {
  if(CanAction()){
    Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false);
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
            this->Collision(attackerOrganism); // Kill
          } else {
            attackerOrganism->Collision(this); // Killed
          }
        }
      }
    }
  }
}

bool Animal::Collision(Organism* attackerOrganism) {
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    this->Breed(attackerOrganism->GetPosition());
    return true;
  } else {
    this->Die();
    return false;
  }
}

void Animal::Breed(const Point &attackerPosition) {
  Point newPosition = this->world.GetRandomPositionForChild(this->GetPosition(), attackerPosition);
  if (newPosition != this->GetPosition()) {
    Organism* newOrganism = this->Clone(newPosition);
    this->world.AddOrganism(newOrganism);
  }
}