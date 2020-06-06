#pragma once
#include "iostream"

typedef unsigned int uint;
enum ID { SL, FS, FC, PM, PC, SN, SC };

class Soldier {
  uint health = 0;
  uint damage_level = 0;
  uint player = 1; //Deafault player 1
  ID id = SL;
  public: 
    Soldier(){};
    virtual ~Soldier(){};
    void setDamage(uint damageL){
      this->damage_level = damageL;
    }
    void setHelath(uint healthL){
      this->health = healthL;
    }
    void setPlayer(uint player_num){
      this->player = player_num;
    }
    void setID(ID id){
        this->id = id;
    }
    uint getHealth(){
      return this->health;
    }
    uint getDamage(){
      return this->damage_level;
    }
    uint getPlayer(){
      return this->player;
    }
    ID getId(){
        return this->id;
    }

    virtual void attack(std::pair<int,int> location, std::vector<std::pair<std::pair<int,int>,Soldier*>> team,
            std::vector<std::pair<std::pair<int,int>,Soldier*>> enemy, std::vector<std::pair<std::vector<Soldier*>,Soldier*>> radiusAndReference) = 0;
    virtual std::string toString(){ return "__";};
};
