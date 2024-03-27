#include "World.h"

  World::World(int w, int h) : width(w), height(h) {
    organismArray = new Organism*[width];
    
    for (int i = 0; i < width; ++i) {
        organismArray[i] = new Organism[height];
    }
  }

  World::~World() {
    // Deallocate memory for each row
    for (int i = 0; i < width; ++i) {
        delete[] organismArray[i];
    }
    delete[] organismArray;
  }

  Organism* World::getOrganismAt(int x, int y) const {
    // Check if the coordinates are within bounds
    if (x >= 0 && x < width && y >= 0 && y < height) {
        return &organismArray[x][y];
    } else {
        return nullptr;
    }
  }
};
