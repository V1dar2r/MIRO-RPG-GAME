#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <fstream>
#include "Player.h"
#include "Monster.h"
#include "GameManager.h"
#include "View.h"
using namespace std;

int main(){
    GameManager game;
    game.startGame();
    return 0;
}