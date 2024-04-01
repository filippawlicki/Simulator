#include "MessageManager.h"

MessageManager::MessageManager() {}

MessageManager::~MessageManager() {}

void MessageManager::AddDeathMessage(const std::string &dead, const std::string &killer) {
  messages.push_back(dead + " died from " + killer + ".");
}

void MessageManager::AddReproductionMessage(const std::string &parent1, const std::string &parent2, const std::string &child) {
  messages.push_back(parent1 + " and " + parent2 + " reproduced " + child + ".");
}

void MessageManager::AddPlantEatingMessage(const std::string &plant, const std::string &animal) {
  messages.push_back(animal + " ate " + plant + ".");
}

void MessageManager::AddAttackRepellMessage(const std::string &attacker, const std::string &defender) {
  messages.push_back(attacker + " attacked " + defender + " but was repelled.");
}

void MessageManager::AddAttackRunawayMessage(const std::string &attacker, const std::string &defender) {
  messages.push_back(attacker + " attacked " + defender + ", but " + defender + " ran away.");
}

void MessageManager::PrintMessages() {
  for (const std::string &message : messages) {
    std::cout << message << std::endl;
  }
}

void MessageManager::ClearMessages() {
  messages.clear();
}