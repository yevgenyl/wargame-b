#pragma once
#include "Board.hpp"
#include "Soldier.hpp"

class FootSoldier: public Soldier {
  public:
    FootSoldier();
    FootSoldier(uint player);
    ~FootSoldier(){};
    Soldier* closestEnemy(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy);
    float distance(int x1, int y1, int x2, int y2);
    bool healthInRange(uint health);
    void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference) override;
    virtual std::string toString() override;
};
