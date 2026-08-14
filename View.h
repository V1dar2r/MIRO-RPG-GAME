#pragma once
#include <iostream>
#include <string>
#include <vector>

class Monster;

class Player;

class GameManager;

class View{
private:
std::vector<std::string> logs;
public:

void printLogHistory();

void addLog(std::string msg);

char ShowMainMenu();

char ShowBattleMenu();

void printEnding(GameManager& g,Player& p,bool isVictory);

void printMap(std::vector<std::vector<Tile>>& m);

char showClassMenu();

void PlayerState(Player& p);

char InputarrowKeys();

void FacingMonster(Player&p, Monster& m);

void cleanScreen();

};
