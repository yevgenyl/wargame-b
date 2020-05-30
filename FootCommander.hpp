#pragma once
#include "Board.hpp"
#include "FootSoldier.hpp"

class FootCommander: public FootSoldier {
  public:
    FootCommander();
    FootCommander(uint player);
    ~FootCommander(){};
    void fullAttack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
            std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
            std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference) override;
    std::string toString() override;
};
