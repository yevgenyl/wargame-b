#include "Board.hpp"
#include "SniperCommander.hpp"
#include "iostream"

using namespace std;

SniperCommander::SniperCommander(){
    this->setID(SC);
    this->setHelath(120);
    this->setDamage(100);
}

SniperCommander::SniperCommander(uint player){
    this->setID(SC);
    this->setHelath(120);
    this->setDamage(100);
    this->setPlayer(player);
}

void SniperCommander::attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                    std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
                    std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    Sniper::attack(location,team,enemy,radiusAndReference);
    fullAttack(location,team,enemy,radiusAndReference);
}

void SniperCommander::fullAttack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
                std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    for(int i = 0; i < team.size(); i++){ // SniperCommander tells his team to attack one by one.
        if(team[i].second->getId() == SN) { // If soldier's type is FootSoldier then he need to perform an attack.
            auto *sniper = (Sniper*)team[i].second; // Current sniper
            std::pair<int,int> sniperLocation = team[i].first; // Current sniper location
            sniper->attack(sniperLocation, team, enemy, radiusAndReference); // Finally attack.
        }
    }
}

string SniperCommander::toString(){
    return "SC";
}