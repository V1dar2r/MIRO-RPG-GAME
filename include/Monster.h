#pragma once
#include <iostream>
#include "Character.h"

class Player;

struct Action;

class Monster: public Character {// 몬스터의 공격력과 체력을 기억하고 관리하는 클래스
    public:
    Monster();
    virtual Action skill(Character& p);

};

class Vargr : public Monster {
    public:
    Vargr();
    Action skill(Character& p);

};

class Eitr : public Monster{
    public:
    Eitr();
    Action skill(Character& p);
};

class Draugr : public Monster{
    public:
    Draugr();
    Action skill(Character& p);
};

class Jormungandr : public Monster {
    public:
    Jormungandr();
    Action skill(Character& p);
};
