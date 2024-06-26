#include "CONSTANTS.h"
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

  humanSuperPowerCooldown = 0;
  humanSuperPowerDuration = -1;
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
  DeleteAllOrganisms();
  DeleteOrganisms();
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

std::vector<Organism*> World::GetOrganisms() const {
  return organisms;
}

void World::DeleteOrganisms() {
  for(Organism* organism : organismsToRemove) {
    delete organism;
  }
  organismsToRemove.clear();
}

void World::DeleteAllOrganisms() {
  for(Organism* organism : organisms) {
    delete organism;
  }
  organisms.clear();
}

void World::MakeTurn() {
  messageManager.ClearMessages();
  HandleSuperPower();
  std::vector<Organism*> organismsToSort = organisms;
  std::sort(organismsToSort.begin(), organismsToSort.end(), [](Organism *a, Organism *b) {
    if (a->GetInitiative() == b->GetInitiative()) {
      return a->GetAge() > b->GetAge();
    }
    return a->GetInitiative() > b->GetInitiative();
  });
  for (Organism *organism : organismsToSort) {
    organism->SetCanAction(true);
  }
  for (Organism *organism : organismsToSort) {
    organism->Action();
  }
  for (Organism *organism : organisms) {
    organism->IncrementAge();
  }
  SetHumanSuperPowerDuration(std::max(-1, GetHumanSuperPowerDuration() - 1));
  if(GetHumanSuperPowerDuration() == -1) {
    SetHumanSuperPowerCooldown(std::max(0, GetHumanSuperPowerCooldown() - 1));
  }
  DeleteOrganisms();
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

Point World::GetRandomPositionAround(const Point &position, const bool &isFree, const int &distance) const {
  Point newPosition;
  int x = position.GetX();
  int y = position.GetY();
  std::vector<Point> directions = {Point(x-distance, y), Point(x+distance, y), Point(x, y-distance), Point(x, y+distance)};
  while(!directions.empty()) {
    int randomIndex = rand() % directions.size();
    newPosition = directions[randomIndex];
    directions.erase(directions.begin() + randomIndex);
    if (IsPositionWithinBounds(newPosition)) {
      if (isFree) {
        if (IsPositionFree(newPosition)) {
          return newPosition;
        }
      } else {
        return newPosition;
      }
    }
  }
  return position; // If no free position was found, return the original position
}

std::vector<Point> World::GetPositionsAround(const Point &position) const {
  Point newPosition;
  int x = position.GetX();
  int y = position.GetY();
  std::vector<Point> directions = {Point(x-1, y), Point(x+1, y), Point(x, y-1), Point(x, y+1)};
  std::shuffle(std::begin(directions), std::end(directions), std::random_device());
  for (int i = 0; i < 4; i++) {
    if (!IsPositionWithinBounds(directions[i])) {
      directions.erase(directions.begin() + i);
    }
  }
  return directions;
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

bool World::IsHumanMoveLegal(const char &input) const {
  Point humanPosition;
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < height; j++) {
      if(worldMap[i][j] != nullptr && worldMap[i][j]->GetSymbol() == HUMAN_SYMBOL) {
        humanPosition = GetOrganismAt(i, j)->GetPosition();
        break;
      }
    }
  }
  Point newPosition = humanPosition;
  switch(input) {
    case 'U':
      newPosition.SetY(humanPosition.GetY() - 1);
      break;
    case 'D':
      newPosition.SetY(humanPosition.GetY() + 1);
      break;
    case 'L':
      newPosition.SetX(humanPosition.GetX() - 1);
      break;
    case 'R':
      newPosition.SetX(humanPosition.GetX() + 1);
      break;
    default:
      return false;
  }
  return IsPositionWithinBounds(newPosition);
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
  organismsToRemove.push_back(organism);
}

void World::MoveOrganism(Organism *organism, const Point &newPosition) {
  Point oldPosition = organism->GetPosition();
  worldMap[oldPosition.GetX()][oldPosition.GetY()] = nullptr;
  worldMap[newPosition.GetX()][newPosition.GetY()] = organism;
  organism->SetPosition(newPosition.GetX(), newPosition.GetY());
}

Point World::GetClosestOrganismPosition(const Point &position, const char &symbol) const {
  int distance = width * height; // Distance that will never be reached
  Point closestPosition = position;
  for(Organism *organism : organisms) {
    if(organism->GetSymbol() == symbol) {
      int x = organism->GetPosition().GetX();
      int y = organism->GetPosition().GetY();
      int newDistance = abs(x - position.GetX()) + abs(y - position.GetY());
      if(newDistance < distance) {
        distance = newDistance;
        closestPosition = organism->GetPosition();
      }
    }
  }
  return closestPosition; // Return the original position if no organism was found
}

Point World::GetRandomPositionForChild(const Point &positionA, const Point &positionB) const {
  std::vector <Point> positions;
  Point directions[] = {Point(0, 1), Point(0, -1), Point(1, 0), Point(-1, 0)};
  for (int i = 0; i < 4; i++) {
    Point newPositionA = positionA + directions[i];
    Point newPositionB = positionB + directions[i];
    if (IsPositionWithinBounds(newPositionA) && IsPositionFree(newPositionA)) {
      positions.push_back(newPositionA);
    }
    if (IsPositionWithinBounds(newPositionB) && IsPositionFree(newPositionB)) {
      positions.push_back(newPositionB);
    }
  }
  std::shuffle(std::begin(positions), std::end(positions), std::random_device());
  if(!positions.empty()) {
    return positions[0];
  }
  return positionA; // If no free position was found, return the original positionA
}

char World::GetHumanInput() const {
  return humanInput;
}

void World::SetHumanInput(const char &input) {
  humanInput = input;
}

int World::GetHumanSuperPowerCooldown() const {
  return humanSuperPowerCooldown;
}

void World::SetHumanSuperPowerCooldown(const int &cooldown) {
  humanSuperPowerCooldown = cooldown;
}

int World::GetHumanSuperPowerDuration() const {
  return humanSuperPowerDuration;
}

void World::SetHumanSuperPowerDuration(const int &duration) {
  humanSuperPowerDuration = duration;
}

bool World::IsHumanDead() const {
  for(Organism *organism : organisms) {
    if(organism->GetSymbol() == HUMAN_SYMBOL) {
      return false;
    }
  }
  return true;
}

void World::HandleSuperPower() {
  if(humanSuperPowerCooldown == 5 && humanSuperPowerDuration == 5) { // Increase the strength of human
    for(Organism *organism : organisms) {
      if(organism->GetSymbol() == HUMAN_SYMBOL) {
        organism->SetStrength(organism->GetStrength() + 5);
      }
    }
  } else if(humanSuperPowerDuration >= 0) { // Lower the strength of human
    for(Organism *organism : organisms) {
      if(organism->GetSymbol() == HUMAN_SYMBOL) {
        organism->SetStrength(organism->GetStrength() - 1);
      }
    }
  }
}