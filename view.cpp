#include "View.h"
#include "Character.h"
#include "Player.h"
#include "GameManager.h"
#include <conio.h>

void View::addLog(std::string msg){
    logs.push_back(msg);
    if (logs.size() > 3) logs.erase(logs.begin());
}

void View::printLogHistory(){
    std::cout << "===== 최근 행동 로그 =====" << '\n';
    for (std::string s:logs){
        std::cout<<s<<'\n';
    }
}

char View::ShowMainMenu(){
    std::cout<< "===================="<<'\n';
    delay(300); 
    std::cout<< "텍스트 미로 RPG"<<'\n';
    delay(300); 
    std::cout<< "===================="<<'\n';
    delay(300);  
    std::cout<<"1. 새로하기"<<'\n';
    delay(100);
    std::cout<<"2. 불러오기"<<'\n';
    delay(100);
    std::cout<<"3. 종료"<<'\n';
    delay(100);
    std::cout<< "===================="<<'\n';
    char c;
    std::cin>>c;
    return c;
}
char View::ShowBattleMenu(){
    std::cout<<"1.일반 공격"<<'\n';
    std::cout<<"2.스킬 사용"<<'\n';    
    char c;
    std::cin>>c;
    return c;
}

void View::printEnding(GameManager&g,Player& p,bool isVictory){
    // 엔딩 화면은 UI 요소로 간주하여 cout 유지
    if (isVictory){
        std::cout<<"==================================="<<'\n';
        std::cout<<" 텍스트 미로 RPG - 탑 탈출 성공! "<<'\n';
        std::cout<<"[ 용사 기록 요약 ]"<<'\n';
        std::cout<<"- 선택 직업 : "<<p.getClass()<<'\n';
        std::cout<<"- 최종 체력 : "<<p.getHP()<<" HP"<<'\n';
        std::cout<<"- 최종 공격력 : "<<p.getAttack()<<'\n';
        std::cout<<"- 최종 스피드 : "<<p.getSpeedStat()<<'\n';
        std::cout<<"- 도달 층수 : " << g.getFloor() <<" / "<< "5" <<"(전체 클리어)"<<'\n';
        std::cout<<"-----------------------------------"<<'\n';
        std::cout << "\"5층의 수호자 요르문간드를 제압하고 마침내 미로 탑의 전설이 되었습니다!\"" << '\n';
        std::cout<<"==================================="<<'\n';
        std::cout<<"아무 키나 누르면 메인 메뉴로 돌아갑니다..."<<'\n';
    }
    else{
        std::cout<<"==================================="<<'\n';
        std::cout<<" 탑 탐험 실패 "<<'\n';
        std::cout<<"[ 패배 기록 요약 ]"<<'\n';
        std::cout<<"- 선택 직업 : "<<p.getClass()<<'\n';
        std::cout<<"- 도달 층수 : " << g.getFloor() <<" Floor"<<'\n';
        std::cout<<"- 사망 원인 : 전투 패배"<<'\n';
        std::cout<<"-----------------------------------"<<'\n';
        std::cout << "\"미로 탑의 깊은 어둠 속에서 용사의 여정이 멈췄습니다...\"" << '\n';
        std::cout<<"==================================="<<'\n';
        std::cout<<"아무 키나 누르면 메인 메뉴로 돌아갑니다..."<<'\n';
    }
    char c;
    std::cin>>c;
}

void View::printMap(std::vector<std::vector<Tile>>& m){
    for (int i=0;i<m.size();i++){
        for (int j=0;j<m[i].size();j++){
            std::cout<<static_cast<char>(m[i][j])<<" ";
        }
        std::cout<<'\n';
    }
}

char View::showClassMenu(){
    std::cout<<"직업을 고르세요."<<'\n'; // UI 메뉴 유지
    delay(300); 
    std::cout<<"1.검사"<<'\n';
    delay(200); 
    std::cout<<"2.궁수"<<'\n';
    delay(200); 
    std::cout<<"3.방패병"<<'\n';
    delay(200); 
    char c;
    std::cin>>c;
    return c;
}

void View::PlayerState(Player& p){
    std::cout<<"플레이어 상태"<<'\n';
    std::cout<<"플레이어 직업 :"<<p.getClass()<<'\n';
    std::cout<<"HP :"<<p.getHP()<<'\n';
    std::cout<<"speed :"<<p.getSpeedStat()<<'\n';
    std::cout<<"attack :"<<p.getAttack()<<'\n';
}

char View::InputarrowKeys(){
    char c;
    std::cin>>c;
    return c;
}

void View::FacingMonster(Player& p , Monster& m){
    std::cout<<"앗! 수풀이 흔들립니다..."<<'\n'; 
    delaySec(1); 
    std::cout<<"야생의 [" + m.getClass() + "] 출현!!"<<'\n'; 
    delaySec(1);
    std::cout<<"전투 발생"<<'\n'; 
    delaySec(1);
    std::cout << "플레이어 HP:" << p.getHP() << '\n';
    std::cout << "몬스터 HP :" << m.getHP() << '\n';
    delaySec(1);
}

void View::cleanScreen(){
    std::cout << "\033[2J\033[1;1H";
}