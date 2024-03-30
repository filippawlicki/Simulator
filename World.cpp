#include "World.h"
#include <stdlib.h>

#include <algorithm>
#include <random>

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

void World::MakeTurn() {
  std::vector<Organism*> organismsToSort = organisms;
  std::sort(organismsToSort.begin(), organismsToSort.end(), [](Organism *a, Organism *b) {
    if (a->GetInitiative() == b->GetInitiative()) {
      return a->GetAge() > b->GetAge();
    }
    return a->GetInitiative() > b->GetInitiative();
  });
  for (Organism *organism : organismsToSort) {
    organism->Action();
  }
  for (Organism *organism : organisms) {
    organism->IncrementAge();
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
  Point directions[] = {Point(x-1, y), Point(x+1, y), Point(x, y-1), Point(x, y+1)};
  std::shuffle(std::begin(directions), std::end(directions), std::random_device());
  for (int i = 0; i < 4; i++) {
    if (IsPositionWithinBounds(directions[i])) {
      if (isFree) {
        if (IsPositionFree(directions[i])) {
          return directions[i];
        }
      } else {
        return directions[i];
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

void World::RemoveOrganism(Organism *organism) {
  Point position = organism->GetPosition();
  worldMap[position.GetX()][position.GetY()] = nullptr;
  organisms.erase(std::remove(organisms.begin(), organisms.end(), organism), organisms.end());
}
