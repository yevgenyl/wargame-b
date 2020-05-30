#pragma once
#include "Board.hpp"
#include "Soldier.hpp"

class Paramedic: public Soldier {
  public:
    Paramedic();
    Paramedic(uint player);
    ~Paramedic(){};
    void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference) override;
    virtual void heal(std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference);
    uint getFullHelathById(ID id);
    std::string toString() override;
};
