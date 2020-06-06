#pragma once
#include "Board.hpp"

class Sniper: public Soldier {
  public:
    Sniper();
    Sniper(uint player);
    ~Sniper(){};
    bool healthInRange(uint health);
    virtual void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                        std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    Soldier* mostPowerfull(std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy);
    virtual std::string toString();
};