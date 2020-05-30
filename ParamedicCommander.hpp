#pragma once
#include "Board.hpp"
#include "Paramedic.hpp"

class ParamedicCommander: public Paramedic {
  public:
    ParamedicCommander();
    ParamedicCommander(uint player);
    ~ParamedicCommander(){};
    void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference) override;
    void fullHeal(std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    virtual std::string toString();
};
