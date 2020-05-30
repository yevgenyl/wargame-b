#include "Paramedic.hpp"
#include "iostream"

using namespace std;

Paramedic::Paramedic(){
    this->setID(PM);
    this->setHelath(100);
}

Paramedic::Paramedic(uint player){
    this->setPlayer(player);
    this->setID(PM);
    this->setHelath(100);
}

void Paramedic::attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    heal(radiusAndReference);
}

void Paramedic::heal(std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    Soldier *paramedic;
    uint index;
    for(int i = 0; i < radiusAndReference.size(); i++){
        if(radiusAndReference[i].second == this) {
            paramedic = radiusAndReference[i].second;
            index = i;
        }
    }
    for(int i = 0; i < radiusAndReference[index].first.size(); i++){
        radiusAndReference[index].first[i]->setHelath(getFullHelathById(radiusAndReference[index].first[i]->getId()));
    }
}

uint Paramedic::getFullHelathById(ID id){
    switch(id){
        case(FS):
            return 100;
        case(FC):
            return 150;
        case(PM):
            return 100;
        case(PC):
            return 200;
        case(SN):
            return 100;
        case(SC):
            return 120;
        default:
            return 0;
    }
}

string Paramedic::toString(){
    return "PM";
}