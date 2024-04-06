#pragma once

#include "Organism.h"
#include "Point.h"
#include "vector"
#include "MessageManager.h"

class World { // Singleton
private:
  int width;
  int height;

  char humanInput;
  int humanSuperPowerCooldown;
  int humanSuperPowerDuration;

  Organism*** worldMap; // 2D array for every square
  std::vector<Organism*> organisms; // Vector for every organism
  std::vector<Organism*> organismsToRemove; // Vector for every organism to be removed

  World(const int &w, const int &h);
public:
  static World& GetInstance(const int &w, const int &h);

  MessageManager messageManager;

  ~World();

  Organism* GetOrganismAt(const int &x, const int &y) const;
  Organism* GetOrganismAt(const Point &position) const;
  Organism*** GetMapOfTheWorld() const;
  std::vector<Organism*> GetOrganisms() const;

  void DeleteOrganisms();
  void DeleteAllOrganisms();

  bool IsPositionFree(const Point &position) const;
  bool IsPositionWithinBounds(const Point &position) const;
  bool IsAnyPositionFree() const;
  bool IsHumanMoveLegal(const char &input) const;
  std::vector<Point> GetPositionsAround(const Point &position) const;

  Point GetRandomFreePosition() const;
  Point GetRandomPositionAround(const Point &position, const bool &isFree, const int &distance) const;

  void MakeTurn();

  void AddOrganism(Organism *organism);
  void RemoveOrganism(Organism *organism);
  void MoveOrganism(Organism *organism, const Point &newPosition);

  Point GetClosestOrganismPosition(const Point &position, const char &symbol) const;

  Point GetRandomPositionForChild(const Point &positionA, const Point &positionB) const;

  int GetWidth() const;
  int GetHeight() const;

  char GetHumanInput() const;
  void SetHumanInput(const char &input);

  int GetHumanSuperPowerCooldown() const;
  void SetHumanSuperPowerCooldown(const int &cooldown);

  int GetHumanSuperPowerDuration() const;
  void SetHumanSuperPowerDuration(const int &duration);

  bool IsHumanDead() const;

  void HandleSuperPower();
};
