#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <string>
#include "Character.h"
#include "View.h"



void delay(int ms){ // 문장 출력이 바로 되는 걸 막기 위한 밀리초단위의 시간 지연
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void delaySec(int sec){ // 문장 출력이 바로 되는 걸 막기 위한 초단위의 시간 지연
    std::this_thread::sleep_for(std::chrono::seconds(sec));
}

int Character::getSpeed(){
    std::uniform_int_distribution<int> dis(0,speed);
        int currentSpeed = dis(gen);
        return currentSpeed;
    }
int Character::getSpeedStat(){
    return speed;
    }

int Character::takeDamage(int damage){ // 몬스터가 데미지를 받았을 때 몬스터의 hp 및 상태를 관리하는 기능
    hp = hp - damage;
    view.addLog(name + ':' + std::to_string(hp));
    delay(800);
    if (hp<=0){
        hp = 0;
        view.addLog(name+" 사망");
        delaySec(1);
        return true;
    }
    return false;
}
std::string Character::getClass(){
    return name;
}

int Character::getAttackDamage(){ //플레이어에게 줄 데미지를 난수를 통해 반환하는 기능
    std::uniform_int_distribution<int> dis(0,attack);
    int damage = dis(gen);
    view.addLog(name+" 공격"+"("+std::to_string(damage)+")");
    delay(800);
    return damage;
}
int Character::getAttackDamage(int damage){
    view.addLog(name+" 공격"+"("+std::to_string(damage)+")");
    delay(800);
    return damage;
}
int Character::getHP(){
    return hp;
}
int Character::getAttack(){
    return attack;
}
void Character::setAttack(int newAttack){
    attack = newAttack;
}