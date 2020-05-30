#include <cmath>
#include "Board.hpp"
#include "FootSoldier.hpp"
#include "iostream"

using namespace std;

FootSoldier::FootSoldier(){
    this->setHelath(100);
    this->setDamage(10);
    this->setID(FS);
}

FootSoldier::FootSoldier(uint player){
    this->setHelath(100);
    this->setDamage(10);
    this->setPlayer(player);
    this->setID(FS);
}

void FootSoldier::attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
        std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy,
        std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference){
    Soldier *closestenemy = closestEnemy(location,enemy);
    if(closestenemy != nullptr) { // If enemy exist around current soldier
        closestenemy->setHelath(closestenemy->getHealth() - this->getDamage());
    }
}

Soldier* FootSoldier::closestEnemy(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy){
    if(!enemy.empty()) { // If enemy exist
        Soldier *closestEnemy = enemy[0].second; // Default closest enemy.
        float closestDistance = INFINITY; // Closest distance.
        for (int i = 0; i < enemy.size(); i++) {
            std::pair<int, int> current = enemy[i].first; // Current enemy location (x,y).
            Soldier *soldier = enemy[i].second; // Current enemy object pointer.
            if(distance(current.first, current.second, location.first, location.second) < closestDistance){ // If smaller distance found.
                closestDistance = distance(current.first, current.second, location.first, location.second); // We set new distance as closest.
                closestEnemy = soldier; // We update closest enemy object pointer.
            }
        }
        return closestEnemy; // Finally return the closest enemy object pointer.
    }else{
        return nullptr; // If there is no enemy left, then return NULL pointer.
    }
}

float FootSoldier::distance(int x1, int y1, int x2, int y2){
    return sqrt(pow(x2 - x1, 2) +
                pow(y2 - y1, 2) * 1.0);
}

string FootSoldier::toString(){
    return "FS";
}
