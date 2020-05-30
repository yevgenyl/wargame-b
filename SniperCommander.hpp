#pragma once
#include "Board.hpp"
#include "Sniper.hpp"

class SniperCommander: public Sniper {
  public:
    SniperCommander();
    SniperCommander(uint player);
    ~SniperCommander(){};
    void fullAttack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                    std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
                    std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    virtual void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                        std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
                        std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    virtual std::string toString();
};