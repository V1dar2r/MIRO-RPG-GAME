#pragma once
#include <iostream>
#include <random>
#include <thread>
#include <chrono>
#include <string>

void delay(int ms); // 문장 출력이 바로 되는 걸 막기 위한 밀리초단위의 시간 지연
void delaySec(int sec); // 문장 출력이 바로 되는 걸 막기 위한 초단위의 시간 지연

class View;

class Character {
protected:
    int hp;
    int attack;
    int speed;
    std::string name;
    inline static std::random_device rd;
    inline static std::mt19937 gen;
    View* view;
public:
    int getSpeed();
    int getSpeedStat();

    virtual int takeDamage(int damage);// 몬스터가 데미지를 받았을 때 몬스터의 hp 및 상태를 관리하는 기능
    std::string getClass();
    virtual int getAttackDamage(); //플레이어에게 줄 데미지를 난수를 통해 반환하는 기능
    int getAttackDamage(int damage);
    int getHP();
    int getAttack();
    void setAttack(int newAttack);
};