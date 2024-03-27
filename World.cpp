#include "World.h"

World::World(const int &w, const int &h) : width(w), height(h) {
  worldMap = new Organism**[width];
  
  for (int i = 0; i < width; ++i) {
    worldMap[i] = new Organism*[height];
    for (int j = 0; j < height; ++j) {
      worldMap[i][j] = nullptr; // Initialize each element to nullptr
    }
  }
}

World::~World() {
  // Deallocate memory for each row
  for (int i = 0; i < width; ++i) {
      for (int j = 0; j < height; ++j) {
          delete worldMap[i][j];
      }
      delete[] worldMap[i];
  }
  
  delete[] worldMap;
}

World& World::getInstance(const int &w, const int &h) {
  static World instance(w, h);
  return instance;
}

Organism* World::getOrganismAt(const int &x, const int &y) const {
  // Check if the coordinates are within bounds
  if (x >= 0 && x < width && y >= 0 && y < height) {
      return worldMap[x][y];
  } else {
      return nullptr;
  }
}

Organism*** World::getMapOfTheWorld() const {
  return worldMap;
}

int World::GetHeight() const {
  return height;
}

int World::GetWidth() const {
  return width;
}
