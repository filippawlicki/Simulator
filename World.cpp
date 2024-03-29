#include "World.h"
#include <stdlib.h>

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

World& World::GetInstance(const int &w, const int &h) {
  static World instance(w, h);
  return instance;
}

Organism* World::GetOrganismAt(const int &x, const int &y) const {
  // Check if the coordinates are within bounds
  if (IsPositionWithinBounds(Point(x, y))) {
      return worldMap[x][y];
  } else {
      return nullptr;
  }
}

Organism* World::GetOrganismAt(const Point &position) const {
  // Check if the coordinates are within bounds
  int x = position.GetX();
  int y = position.GetY();
  if (IsPositionWithinBounds(Point(x, y))) {
      return worldMap[x][y];
  } else {
      return nullptr;
  }
}

Organism*** World::GetMapOfTheWorld() const {
  return worldMap;
}

void World::MakeTurn() { // TODO: Implement sorting of organisms by initiative and age before making a turn
  for (int i = 0; i < organisms.size(); i++) {
    organisms[i]->Action();
  }
}

Point World::GetRandomFreePosition() const {
  if(!IsAnyPositionFree()) {
    return Point(-1, -1); // Return if there are no free positions
  }
  Point position;
  do {
    position.SetX(rand() % width);
    position.SetY(rand() % height);
  } while (!IsPositionFree(position));
  return position;
}

Point World::GetRandomPositionAround(const Point &position, const bool &isFree) const {
  Point newPosition;
  int x = position.GetX();
  int y = position.GetY();
  for(int i = -1; i < 2; i++) {
    for(int j = -1; j < 2; j++) {
      if((IsPositionWithinBounds(Point(x + i, y + j))) && (GetOrganismAt(x + i, y + j) == nullptr) == isFree) {
        newPosition.SetX(x + i);
        newPosition.SetY(y + j);
        return newPosition;
      }
    }
  }
  return position; // If no free position was found, return the original position
}

bool World::IsPositionFree(const Point &position) const {
  return GetOrganismAt(position) == nullptr;
}

bool World::IsPositionWithinBounds(const Point &position) const {
  int x = position.GetX();
  int y = position.GetY();
  return x >= 0 && x < width && y >= 0 && y < height;
}

bool World::IsAnyPositionFree() const {
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      if(worldMap[i][j] == nullptr) {
        return true;
      }
    }
  }
  return false;
}

void World::AddOrganism(Organism *organism) {
  worldMap[organism->GetPosition().GetX()][organism->GetPosition().GetY()] = organism;
  organisms.push_back(organism);
}

int World::GetHeight() const {
  return height;
}

int World::GetWidth() const {
  return width;
}
