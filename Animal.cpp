#include "World.h"
#include "Animal.h"

Animal::  Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color)
  : Organism(world, position, symbol, strength, initiative, color) {}

Animal::~Animal() {}

void Animal::Action() {
  Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false);
  if (newPosition != this->GetPosition()) {
    Organism* attackerOrganism = this->world.GetOrganismAt(newPosition);
    if (attackerOrganism == nullptr) { // Free space
      this->SetPosition(newPosition.GetX(), newPosition.GetY());
    } else { // Collision
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

bool Animal::Collision(Organism* attackerOrganism) {
  if(dynamic_cast<const void*>(this) == dynamic_cast<const void*>(attackerOrganism)) { 
    this->Breed();
    return true;
  } else {
    this->Die();
  }
}

void Animal::Breed() {
  Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false);
  if (newPosition != this->GetPosition()) {
    Organism* newOrganism = this->Clone(newPosition);
    this->world.AddOrganism(newOrganism);
  }
}