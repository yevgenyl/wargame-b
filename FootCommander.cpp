#include "FootCommander.hpp"
#include "iostream"

using namespace std;

FootCommander::FootCommander(){
    this->setHelath(150);
    this->setDamage(20);
    this->setID(FC);
}

FootCommander::FootCommander(uint player){
    this->setHelath(150);
    this->setDamage(20);
    this->setPlayer(player);
    this->setID(FC);
}

void FootCommander::attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team, std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    FootSoldier::attack(location,team,enemy,radiusAndReference); // Step 1: FootCommander performs an attack.
    fullAttack(location,team,enemy,radiusAndReference); // Step 2: All team performs an attack.
}

void FootCommander::fullAttack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team, std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    for(int i = 0; i < team.size(); i++){ // FootCommander tells his team to attack one by one.
        Soldier *soldier = team[i].second; // Current soldier
        std::pair<int,int> soldierLocation = team[i].first; // Current soldier location
        if(soldier->getId() == FS) // If soldier's type is FootSoldier then he need to perform an attack.
            soldier->attack(soldierLocation,team,enemy,radiusAndReference); // Finally attack.
    }
}

string FootCommander::toString(){
    return "FC";
}
