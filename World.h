#pragma once

#include "Organism.h"

#include "vector"

class World {
private:
  int width;
  int height;

  vector  

public:
  World(int w, int h) : width(w), height(h) {}

  ~World() {}

  Organism* getOrganismAt(int x, int y) const {}

  int GetWidth() const;
  int GetHeight() const;
};
