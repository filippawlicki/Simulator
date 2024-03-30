#include "World.h"
#include "Animal.h"
#include <iostream>
#include <unistd.h>

Animal::  Animal(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color)
  : Organism(world, position, symbol, strength, initiative, color) {}

Animal::~Animal() {}

void Animal::Action() {
  Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), false);
  if (newPosition != this->GetPosition()) {
    Organism* attackerOrganism = this->world.GetOrganismAt(newPosition);
    if (attackerOrganism == nullptr) { // Free space
      this->world.MoveOrganism(this, newPosition);
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
  if(this->GetSymbol() == attackerOrganism->GetSymbol()){
    std::cout << "BREED";
    sleep(1);
    this->Breed();
    return true;
  } else {
    this->Die();
    return false;
  }
}

void Animal::Breed() {
  Point newPosition = this->world.GetRandomPositionAround(this->GetPosition(), true);
  if (newPosition != this->GetPosition()) {
    Organism* newOrganism = this->Clone(newPosition);
    this->world.AddOrganism(newOrganism);
  }
}