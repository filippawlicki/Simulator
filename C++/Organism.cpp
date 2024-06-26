#include "CONSTANTS.h"

#include "World.h"
#include "Organism.h"
#include <iostream>

Organism::Organism(World &world, const Point &position, const char &symbol, const int &strength, const int &initiative, const std::string &color, const std::string &name) :
world(world), position(position), symbol(symbol), strength(strength), initiative(initiative), color(color), name(name) {canAction = false; age = 0;}

Point Organism::GetPosition() const {
  return position;
}

void Organism::SetPosition(const int &x, const int &y) {
  position.SetX(x);
  position.SetY(y); 
}

int Organism::GetAge() const {
  return age;
}

void Organism::IncrementAge() {
  age++;
}

int Organism::GetInitiative() const {
  return initiative;
}

int Organism::GetStrength() const {
  return strength;
}


void Organism::SetStrength(const int &strength) {
  this->strength = strength;
}

char Organism::GetSymbol() const {
  return symbol;
}

std::string Organism::GetName() const {
  return name;
}

void Organism::Draw() {
  std::cout << color << symbol << RESET_COLOR;
}

void Organism::Die() {
  this->world.RemoveOrganism(this);
}

bool Organism::CanAction() const {
  return canAction;
}

void Organism::SetCanAction(const bool &canAction) {
  this->canAction = canAction;
}