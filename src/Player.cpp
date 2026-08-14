#include <iostream>
#include "Player.h"
#include "monster.h"

Player::Player(){
    gen.seed(rd());  // 난수 초기화          
    x=4;
    y=4;
    name = "player";
}
void Player::setHP(int newHp){ 
    hp = newHp;
}
void Player::setXY(int newX,int newY){ 
    x = newX;
    y = newY;
}
void Player::setSpeed(int newSpeed){
    speed = newSpeed;
}
void Player::setAttack(int newAttack){
    attack = newAttack;
}
int Player::getX() const{
    return x;
}
int Player::getY() const{ 
    return y;
}
void Player::setPosition(int new_x,int new_y){ // 새로운 위치값으로 변경하는 기능
    x= new_x;
    y= new_y;
}
Action Player::skill(){ return {0,0,false};}

Archer::Archer(){
    hp = 70;
    attack = 30;
    speed = 30;
    name = "Archer";
}
Action Archer::skill(){
    Action action;
    action.attack = attack*1.2;
    action.bonusSpeed = 9999;
    action.isGuarding = false;
    view.addLog("데스 스팅");
    delay(800); // 0.8초 기다리기
    return action;
}
SwordsMan::SwordsMan(){
    hp = 100;
    attack =24;
    speed = 20;
    name = "SwordsMan";
}
Action SwordsMan::skill(){
    Action action;
    action.attack = attack*1.5;
    action.bonusSpeed = 0;
    action.isGuarding = false;
    view.addLog("익스큐션");
    delay(800); // 0.8초 기다리기

    return action;    
}
Shielder::Shielder(){
    hp = 140;
    attack = 16;
    speed = 10;
    name = "Shielder";
}
Action Shielder::skill() {
    Action action;
    action.attack = attack;
    action.bonusSpeed = 0;
    action.isGuarding = true;
    view.addLog("이지스의 가호");
    delay(800);
    view.addLog("몬스터의 공격을 방어했습니다!");
    return action;
}