#pragma once

#include <vector>
#include <iostream>
#include <string>

class MessageManager {
private:
  std::vector<std::string> messages;
public:
  MessageManager();
  ~MessageManager();

  void AddDeathMessage(const std::string &dead, const std::string &killer);
  void AddReproductionMessage(const std::string &parent1, const std::string &parent2, const std::string &child);
  void AddPlantEatingMessage(const std::string &plant, const std::string &animal);
  void AddAttackRepellMessage(const std::string &attacker, const std::string &defender);
  void AddAttackRunawayMessage(const std::string &attacker, const std::string &defender);
  void PrintMessages();
  void ClearMessages();
};