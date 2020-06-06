#include "Board.hpp"
#include "Sniper.hpp"

using namespace std;

Sniper::Sniper(){
    this->setID(SN);
    this->setHelath(100);
    this->setDamage(50);
}

Sniper::Sniper(uint player){
    this->setID(SN);
    this->setHelath(100);
    this->setDamage(50);
    this->setPlayer(player);
}

void Sniper::attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
                    std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    Soldier *mostPowefull = mostPowerfull(enemy);
    if(mostPowefull != nullptr) {
        if(healthInRange(mostPowefull->getHealth() - this->getDamage())) {
            mostPowefull->setHelath(mostPowefull->getHealth() - this->getDamage());
        } else{
            mostPowefull->setHelath(0);
        }
    }
}

Soldier* Sniper::mostPowerfull(std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy){
    uint health = 0;
    Soldier *mostPowerfull;
    if(!enemy.empty()) {
        mostPowerfull = enemy[0].second;
        for (int i = 0; i < enemy.size(); i++) {
            if(healthInRange(mostPowerfull->getHealth()))
            if(enemy[i].second->getHealth() > health){
                health = enemy[i].second->getHealth();
                mostPowerfull = enemy[i].second;
            }
        }
    }else{
        return nullptr;
    }
    return mostPowerfull;
}

bool Sniper::healthInRange(uint health){
    return health > 0 && health <=200;
}

string Sniper::toString(){
    return "SN";
}