#include "ParamedicCommander.hpp"

ParamedicCommander::ParamedicCommander(){
    this->setHelath(200);
    this->setID(PC);
}

ParamedicCommander::ParamedicCommander(uint player){
    this->setHelath(200);
    this->setID(PC);
    this->setPlayer(player);
}

void ParamedicCommander::attack(std::pair<int,int> location,
        std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
            std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    Paramedic::heal(radiusAndReference);
    fullHeal(radiusAndReference);
}

void ParamedicCommander::fullHeal(std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    for(int i = 0; i < radiusAndReference.size(); i++){
        if(radiusAndReference[i].second->getId() == PM) {
            auto *current = (Paramedic *) radiusAndReference[i].second;
            std::vector<Soldier *> radius = radiusAndReference[i].first;
            current->heal(radiusAndReference);
        }
    }
}

std::string ParamedicCommander::toString(){
    return "PC";
}