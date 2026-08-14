#pragma once
#include <iostream>
#include "Character.h"
#include "GameManager.h"

class Monster;
struct Action;

class Player : public Character {// 플레이어의 체력,위치,공격력을 기억하고 관리하는 클래스
    private:
    int x,y;
    public:
        Player();
        void setHP(int newHp);
        
        void setXY(int newX,int newY);
        
        void setSpeed(int newSpeed);
        
        void setAttack(int newAttack);
        
        int getX() const;
        
        int getY() const; 
        
        void setPosition(int new_x,int new_y); // 새로운 위치값으로 변경하는 기능
        
        virtual Action skill() ;
};

class Archer : public Player{
    public:
    Archer();

    Action skill();
};

class SwordsMan : public Player{
    public:
    SwordsMan();

    Action skill();
};

class Shielder : public Player{
    public:
    Shielder();
   
    Action skill();

};