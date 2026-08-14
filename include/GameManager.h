#pragma once
#include <iostream>
#include <fstream>
#include <random>
#include <stack>
#include <string>
#include <memory>
#include "Monster.h"
#include "Player.h"
#include "View.h"

#define max_size 15 // 미로 크기
#define max_floor 5 // 최대 층

struct Action{
    int attack;
    int bonusSpeed;
    bool isGuarding;
};


enum class Tile : char{
    Path = '0',
    Destination = 'D',
    Wall = '1',
    StartingPoint = 'S',
    Monster = 'M',
    Player = 'P',
    Jormungandr = 'J',
    HealingPack = 'H',
    AttackEnhancement = 'W',
};


class GameManager{ //게임 조작 및 설정에 관한 관리하는 클래스
    private:
    std::vector<std::string> original_maze;
    std::vector<std::vector<Tile>> maze;
    inline static std::random_device rd;
    inline static std::mt19937 gen;
    int currentFloor = 0;
    std::vector<std::string> logs;
    View view;
    
    public:
    GameManager();

    void addLog(std::string msg);

    bool startGame();

    void setFloor(int floor) ;

    int getFloor() const;

    void resetMaze();

    std::vector<std::vector<Tile>> getMap() const;

    std::unique_ptr<Player> choiceClass();

    void store(std::ofstream& saveFile);
    
    void load(std::ifstream& loadFile);

    bool speedTest(int PlayerSpeed,int MonsterSpeed);

    bool battle(Player& p,Monster& m);

    void generateMap(Player& p);

    void printEnding(Player& p,bool isVictory);
    
    void printMap();
    
    char asciiCodeTest (int n);

    bool move(Player& p, char c);

    bool playing(bool loading);

    bool checkEvent(int next_x, int next_y, Player& p);
};