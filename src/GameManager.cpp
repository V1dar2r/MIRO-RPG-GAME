#include <iostream>
#include <vector>
#include <fstream>
#include <conio.h>
#include <random>
#include <stack>
#include <memory>
#include <string>
#include "Monster.h"
#include "Player.h"
#include "GameManager.h"
#include "View.h"

#define max_size 15 // 미로 크기
#define max_floor 5 // 최대 층


GameManager::GameManager(){
    gen.seed(rd());
    original_maze = {
        "S00100000100000",
        "110101110101110",
        "000001000101000",
        "011111011101011",
        "0000P1000001000",
        "011101111111110",
        "00M000000000010",
        "011111111011010",
        "00000001M001010",
        "111111010101010",
        "0000010101M1000",
        "011101010111110",
        "010001010000000",
        "010111011111110",
        "11111111111110D"
    }; 
}
bool GameManager::startGame(){
    char k;
    bool isPlaying=true;
    bool exit;
    
    while (isPlaying){
        char userInput = view.ShowMainMenu();
        switch (userInput)
        {
        case '1':
            view.addLog("새로하기가 선택되었습니다.");
            delay(800); 
            exit = playing(false);
            setFloor(1);
            if (exit) return true; 
            break;
        case '2':
            view.addLog("불러오기가 선택되었습니다.");
            delay(800); 
            exit = playing(true);
            if (exit) return true;
            break;
        case '3':
            view.addLog("게임을 종료합니다."); // 문법 오류 수정됨
            delay(800); 
            isPlaying = false; 
            break;
        default: 
            view.addLog("잘못 입력하셨습니다."); 
            delay(500); 
            view.addLog("다시 입력해주세요!!"); 
            delay(500); 
            break;
        }
    }
    return true;
}
void GameManager::setFloor(int floor) {
    currentFloor = floor;
}
int GameManager::getFloor(){
    return currentFloor;
}
void GameManager::resetMaze(){ 
    maze.assign(max_size,std::vector<Tile>(max_size,Tile::Path));
    for (int i = 0;i<max_size;i++){
        for (int j = 0;j<max_size;j++){
            maze[i][j] = static_cast<Tile>(original_maze[i][j]);
        }
    }
}
std::vector<std::vector<Tile>> GameManager::getMap(){
    return maze;
}
void GameManager::store(std::ofstream& saveFile){ 
    for (int i=0;i<max_size;i++){
        for (int j = 0;j<max_size;j++){
            char tileCode = static_cast<char> (maze[i][j]);
            saveFile<<tileCode;
        }
    }
}

void GameManager::load(std::ifstream& loadFile){ 
    for (int i=0;i<max_size;i++){ 
        for (int j = 0;j<max_size;j++){
            char tileCode = 0;
            loadFile >> tileCode;
            maze[i][j] = static_cast<Tile>(tileCode);
        }
    }
}
bool GameManager::speedTest(int PlayerSpeed,int MonsterSpeed){ 
    if (PlayerSpeed >= MonsterSpeed){
        view.addLog("플레이어 선공"); 
        delay(800); 
        return true;
    }
    else{
        view.addLog("몬스터 선공"); 
        delay(800); 
        return false;
    }
}
bool GameManager::battle(Player& p,Monster& m){ 
    int k;
    int cnt = 0;
    int MonsterTurn = 0;
    std::uniform_int_distribution<int> mons(0,100);
    
    while (true){
        // 전투 메뉴는 UI이므로 cout 유지
        char userInput = view.ShowBattleMenu();
        int monsterAttack = mons(gen)%2;
        int PlayerDamage;
        int MonsterDamage;
        Action ac = {0,0,false};
        MonsterTurn++;
        
        if (m.getClass() == "Jormungandr" && MonsterTurn == 3){
            m.setAttack(m.getAttack()+m.getAttack()*0.2);
            MonsterTurn = 0;
        }
        if (userInput == '1'){
            PlayerDamage = p.getAttackDamage();
        }
        else if (userInput == '2'){
            if (cnt == 3){
                view.addLog("스킬을 더이상 사용할 수 없습니다.");
                continue;
            }
            ac = p.skill();
            PlayerDamage = ac.attack;
            cnt++;
        }
        else {
            view.addLog("키를 잘못 입력하셨습니다."); 
            view.addLog("다시 입력해주세요."); 

        }
        if (monsterAttack == 0){
            MonsterDamage = m.getAttackDamage();
        }
        else if (monsterAttack == 1){
            MonsterDamage = m.skill(p).attack;
        } 
        if (speedTest(p.getSpeed()+ac.bonusSpeed,m.getSpeed())){
            bool MonsterDead = m.takeDamage(PlayerDamage);
            if (MonsterDead) return true;
            if (ac.isGuarding){
                view.addLog("스킬로 몬스터의 공격이 무효화되었습니다.");
                continue;
            }
            bool PlayerDead = p.takeDamage(MonsterDamage);
            if (PlayerDead) return false;
        }
        else{
            if (!ac.isGuarding){
                bool PlayerDead = p.takeDamage(MonsterDamage);
                if (PlayerDead) return false;    
            }
            else{
                view.addLog("스킬로 몬스터의 공격이 무효화되었습니다.");

            }
            bool MonsterDead = m.takeDamage(PlayerDamage);
            if (MonsterDead) return true;            
        }

    }
    return true;
}
void GameManager::generateMap(Player& p){ 
    std::uniform_int_distribution<int> dis(0,14);
    int start_x = dis(gen);
    int start_y = dis(gen);
    std::vector<std::vector<Tile>> m(max_size,std::vector<Tile>(max_size,Tile::Wall));
    std::vector<int> dx = {0,0,2,-2};
    std::vector<int> dy = {2,-2,0,0};
    m[start_x][start_y] = Tile::Player;
    p.setPosition(start_x,start_y);
    std::stack<std::pair<int,int>> s;
    s.push({dis(gen),dis(gen)});
    s.push({start_x,start_y});
    std::vector<std::pair<int,int>> monsterXY;
    
    while (!s.empty()){
        int cx = s.top().first;
        int cy = s.top().second;
        s.pop();
        std::vector<std::pair<int,int>> neighbor;
        for (int i=0;i<4;i++){
            int nx = cx+dx[i];
            int ny = cy+dy[i];
            if (nx > 0 && nx<max_size && ny > 0 && ny < max_size && m[nx][ny] ==Tile::Wall){
                neighbor.push_back({dx[i],dy[i]});
            } 
        }
        if (neighbor.size() > 0){
            std::uniform_int_distribution dis2(0,(int)neighbor.size()-1);
            int idx = dis2(gen);
            m[cx+neighbor[idx].first/2][cy+neighbor[idx].second/2] = Tile::Path;
            m[cx+neighbor[idx].first][cy+neighbor[idx].second]= Tile::Path;
            s.push({cx+neighbor[idx].first,cy+neighbor[idx].second});
            monsterXY.push_back({cx+neighbor[idx].first/2,cy+neighbor[idx].second/2});
            monsterXY.push_back({cx+neighbor[idx].first,cy+neighbor[idx].second});
        }
    }
    
    if (!monsterXY.empty()){
        std::uniform_int_distribution<int> monsterGPS(0,(int)monsterXY.size()-1);
        std::vector<int> visited(monsterXY.size(),0);
        if (currentFloor == max_floor) {
            int xy = monsterGPS(gen);
            visited[xy] = 1;
            m[monsterXY[xy].first][monsterXY[xy].second] = Tile::Monster;
        }
        else{
            int destination = monsterGPS(gen);
            m[monsterXY[destination].first][monsterXY[destination].second] = Tile::Destination;
            visited[destination] = 1;
        }
        for (int i = 0;i<5;i++){
            int xy = monsterGPS(gen);
            if (visited[xy]==1){
                i--;
                continue;
            }
            visited[xy] = 1;
            m[monsterXY[xy].first][monsterXY[xy].second] = Tile::Monster;
        }
        for (int i = 0;i<2;i++){
            int xy = monsterGPS(gen);
            if (visited[xy]==1){
                i--;
                continue;
            }
            visited[xy] = 1;                
            m[monsterXY[xy].first][monsterXY[xy].second] =  (Tile::HealingPack);
        }
        for (int i = 0;i<2;i++){
            int xy = monsterGPS(gen);
            if (visited[xy]==1){
                i--;
                continue;
            }
            visited[xy] = 1;                
            m[monsterXY[xy].first][monsterXY[xy].second] =  (Tile::AttackEnhancement);
        }            
    }
    maze = m;
}

char GameManager::asciiCodeTest (int n){
    if (n == 72) return 'w';
    else if (n == 80) return 's';
    else if (n == 75) return 'a';
    else if (n == 77) return 'd';
    else return (char) n;
}
bool GameManager::move(Player& p,char c){ 
    int next_x = p.getX();
    int next_y = p.getY();
    c = asciiCodeTest((int)c);
    
    switch (c) {
    case 'w':
        next_x = p.getX()-1;
        next_y = p.getY();
        break;
    case 's':
        next_x = p.getX()+1;
        next_y = p.getY();
        break;
    case 'd':
        next_x = p.getX();
        next_y = p.getY()+1;
        break;
    case 'a':
        next_x = p.getX();
        next_y = p.getY()-1;
        break;
    case 'p':{ 
        std::ofstream saveFile("save.txt"); 
        if (saveFile.is_open()){
            saveFile<<p.getClass()<<'\n';
            saveFile<<p.getHP()<<'\n'; 
            saveFile<<p.getX()<<'\n'; 
            saveFile<<p.getY()<<'\n'; 
            saveFile<<p.getSpeedStat()<<'\n';
            saveFile<<p.getAttack()<<'\n';
            store(saveFile); 
            saveFile<<getFloor();
            saveFile.close(); 
            view.addLog("저장이 완료되었습니다."); 
            return 0; 
        }   
        else{ 
            view.addLog("저장이 실패하였습니다."); 
            view.addLog("다시 시도해주세요."); 
        }
        return true;
        }
    default: 
        view.addLog("입력이 잘못되었습니다."); 
        view.addLog("다시 입력하세요"); 
        return true;
    }
    return checkEvent(next_x,next_y,p);
}

std::unique_ptr<Player> GameManager::choiceClass(){
    std::unique_ptr<Player> p;
    char userInput = view.showClassMenu();
    if (userInput=='1') p = std::make_unique <SwordsMan>();
    else if (userInput=='2') p = std::make_unique <Archer>();
    else if (userInput=='3') p = std::make_unique <Shielder>();
    else{
        view.addLog("다시 입력하세요"); // 잘못된 입력은 로그로 처리
        delay(500); 
        p = choiceClass();
    }
    return p;
}
bool GameManager::playing(bool loading){ 
    char c;
    std::unique_ptr<Player> p = nullptr; 
    bool goal = true;
    resetMaze();
    
    if (loading){ 
        std::ifstream loadFile("save.txt"); 
        if (loadFile.is_open()){
            int loadHp,loadX,loadY,loadAttack,loadSpeed,loadFloor;
            std::string loadClass;
            loadFile >> loadClass;
            loadFile >> loadHp;
            loadFile >> loadX;
            loadFile >> loadY;
            loadFile >> loadSpeed;
            loadFile >> loadAttack;
            load(loadFile); 
            loadFile >> loadFloor;
            if (loadClass == "Archer") p = std::make_unique<Archer>();
            else if(loadClass == "SwordsMan") p = std::make_unique<SwordsMan>();
            else if (loadClass == "Shielder") p = std::make_unique<Shielder>();
            p->setHP(loadHp); 
            p->setXY(loadX,loadY); 
            p->setAttack(loadAttack);
            p->setSpeed(loadSpeed);
            setFloor(loadFloor);
            loadFile.close();
            view.addLog("불러오기가 성공하였습니다."); 
        }
        else { 
            view.addLog("불러오기가 실패하였습니다."); 
            return false;
        }
    }
    else{ 
        view.addLog("미로가 시작되었습니다"); 
        p = choiceClass();
    }
    
    while (goal){ 
        view.cleanScreen();
        view.printMap(maze); 
        // 상태창 출력은 UI이므로 cout 유지
        view.PlayerState(*p);
        view.addLog("키를 입력하세요");
        char UserInput = view.InputarrowKeys();
        goal = move(*p,UserInput);
        if (!goal) return true;
        // 저장된 로그 출력
        view.printLogHistory();
    }
    return true;
}
bool GameManager::checkEvent(int next_x,int next_y,Player& p){ 
    if (next_x<0 || next_x>max_size-1 || next_y<0 || next_y>max_size-1){ 
        view.addLog("이곳은 지나갈 수 없습니다."); // 중복 cout 제거
        delay(500);
        view.addLog("다시 입력해주세요"); // 중복 cout 제거
        delay(500);
    }
    else if (maze[next_x][next_y]== Tile::Destination) { 
        view.addLog("미로 탈출에 성공 했습니다."); 
        delaySec(1); 
        currentFloor++;
        view.addLog("다음 층으로 이동합니다!"); // 중복 cout 제거
        delaySec(1);
        generateMap(p); 
    }
    else if (maze[next_x][next_y]== Tile::Wall) { 
        view.addLog("이곳은 지나갈 수 없습니다."); 
        delay(500);
        view.addLog("다른 방향을 선택하세요."); 
        delay(500);
    }
    else if (maze[next_x][next_y]== Tile::Monster){ 
        std::unique_ptr<Monster> monster = nullptr; 
        std::uniform_int_distribution<int> mobGen(0,2);
        int mobType = mobGen(gen);
        if (mobType == 0) monster = std::make_unique <Vargr>();
        else if (mobType == 1) monster = std::make_unique <Eitr>();
        else if (mobType == 2) monster = std::make_unique <Draugr>();
        view.FacingMonster(p,*monster);
        bool destiny = battle(p,*monster);  
        if (!destiny){ 
            view.addLog("미로 탈출 실패했습니다."); 
            delaySec(2);
            view.printEnding(*this,p,false);
            return false;
        }
        maze[p.getX()][p.getY()]=(Tile::Path);  
        maze[next_x][next_y]= (Tile::Player); 
        p.setPosition(next_x,next_y); 
        delaySec(2); 
        view.addLog("몬스터와의 전투에서 승리했습니다."); // 중복 cout 제거
    }
    else if(maze[next_x][next_y] ==  Tile::Jormungandr){
        std::unique_ptr<Monster> monster = std::make_unique <Jormungandr>(); 
        view.FacingMonster(p,*monster);
        
        delaySec(1);
        
        bool destiny = battle(p,*monster); 
        
        if (!destiny){ 
            view.addLog("몬스터와의 전투에서 패배했습니다."); // 중복 cout 제거
            view.printEnding(*this,p,false);
            delaySec(2);
        }
        else{
            maze[p.getX()][p.getY()]=Tile::Path;  
            maze[next_x][next_y]=Tile::Player; 
            p.setPosition(next_x,next_y); 
            delaySec(2); 
            view.addLog("미로 탈출에 성공했습니다"); // 중복 cout 제거
            view.printEnding(*this,p,true);
        }
        return false;
    }
    else {  
        if (maze[next_x][next_y] ==  Tile::HealingPack){
            view.addLog("체력 물약 발견!!"); // 중복 cout 제거
            delaySec(1); 
            view.addLog("체력을 20 회복합니다!!"); // 중복 cout 제거
            p.setHP(p.getHP()+20);
            delaySec(2); 
        }
        else if (maze[next_x][next_y] == Tile::AttackEnhancement){
            view.addLog("공격력 강화 아이템 발견!!"); // 중복 cout 제거
            delaySec(1);
            view.addLog("공격력이 5 강화되었습니다!!"); // 중복 cout 제거
            p.setAttack(p.getAttack()+5);
            delaySec(2);
        }
        maze[p.getX()][p.getY()]=Tile::Path; 
        maze[next_x][next_y]= Tile::Player; 
        p.setPosition(next_x,next_y); 
    }
    return true;
}