#include <iostream>
#include "Monster.h"

class Player;

   
Monster::Monster(){
    std::uniform_int_distribution<int> dis(1,100);
    std::uniform_int_distribution<int> dis2(1,50);
    gen.seed(rd()); // 난수 초기화
    hp = dis(gen);
    speed = dis2(gen);
    attack = dis2(gen);
    name = "monster";
}


Vargr::Vargr(){
    hp = 20;
    attack =22;
    speed = 26;
    name = "Vargr";
}
int Vargr::skill(Character& p){
    int mySpeed = getSpeed();
    int pSpeed = p.getSpeed();
    int damage = attack;
    if (mySpeed > pSpeed){
        damage += mySpeed-pSpeed;
    }
    return damage;
}

Eitr::Eitr(){
    hp = 15;
    attack = 8;
    speed = 6;
    name = "Eitr";
}
int Eitr::skill(Character& p){
    int damage = attack+hp*0.3;
    hp = hp - hp*0.3;
    return damage;
}

Draugr::Draugr(){
    hp = 30;
    attack = 16;
    speed = 16;
    name = "Draugr";
}
int Draugr::skill(Character& p){
    int maxHp = 30;
    int lostHp = maxHp - hp;
    int damage = attack + (lostHp/2);
    return damage;
}
Jormungandr::Jormungandr(){
    hp = 120;
    attack = 30;
    speed = 20;
    name = "Jormungandr";
}
int Jormungandr::skill(Character& p){
    int damage = attack+ attack*0.5;
    return damage;
}