#pragma once
#include <iostream>
#include "Character.h"

class Player;

class Monster: public Character {// 몬스터의 공격력과 체력을 기억하고 관리하는 클래스
    public:
    Monster();
    virtual int skill(Character& p);

};

class Vargr : public Monster {
    public:
    Vargr();
    virtual int skill(Character& p);

};

class Eitr : public Monster{
    public:
    Eitr();
    virtual int skill(Character& p);
};

class Draugr : public Monster{
    public:
    Draugr();
    virtual int skill(Character& p);
};

class Jormungandr : public Monster {
    public:
    Jormungandr();
    virtual int skill(Character& p);
};