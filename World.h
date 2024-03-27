#pragma once

#include "Organism.h"

#include "vector"

class World { // Singleton
private:
  int width;
  int height;

  Organism*** worldMap; // 2D array for every square
  std::vector<Organism> organisms; // Vector for every organism

  World(const int &w, const int &h) : width(w), height(h) {}
public:
  static World& getInstance(const int &w, const int &h) {};

  ~World() {}

  Organism* getOrganismAt(const int &x, const int &y) const {}
  Organism*** getMapOfTheWorld() const {}

  int GetWidth() const;
  int GetHeight() const;
};
