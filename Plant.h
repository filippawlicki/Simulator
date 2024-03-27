#pragma once

#include "Organism.h"

class Plant : public Organism {
private:
  double spreadProbability;
protected:
  double GetSpreadProbability() const;
  void TryToSpread();
public:
  Plant(World &world, const Point &position, const char &symbol, const int &strength, 
  const double &spreadProbability);

  ~Plant();

  virtual void Action() override;
  virtual bool Collision(Organism* attackerOrganism) override;
};