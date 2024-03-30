#pragma once

#include "Organism.h"
#include "Point.h"
#include "vector"

class World { // Singleton
private:
  int width;
  int height;

  Organism*** worldMap; // 2D array for every square
  std::vector<Organism*> organisms; // Vector for every organism

  World(const int &w, const int &h);
public:
  static World& GetInstance(const int &w, const int &h);

  ~World();

  Organism* GetOrganismAt(const int &x, const int &y) const;
  Organism* GetOrganismAt(const Point &position) const;
  Organism*** GetMapOfTheWorld() const;

  bool IsPositionFree(const Point &position) const;
  bool IsPositionWithinBounds(const Point &position) const;
  bool IsAnyPositionFree() const;

  Point GetRandomFreePosition() const;
  Point GetRandomPositionAround(const Point &position, const bool &isFree) const;

  void MakeTurn();

  void AddOrganism(Organism *organism);
  void RemoveOrganism(Organism *organism);
  void MoveOrganism(Organism *organism, const Point &newPosition);

  Point GetRandomPositionForChild(const Point &positionA, const Point &positionB) const;

  int GetWidth() const;
  int GetHeight() const;
};
