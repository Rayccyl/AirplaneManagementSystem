//
// Created by 23689 on 2023/7/4.
//
#include "CDRU.h"
#include <vector>
#include <iomanip>

extern linklist* recordInMemory;
void searchAsTerminus(std::string direction){
    if(direction=="empty") return;
    linklist* start=recordInMemory;
    flight show;
    //目的地 出发日 航班号 飞机号  特等座满座率 一等座满座率 二等座满座率 总满座率
    while ((start=terminusSearch(direction,start))!=nullptr){
        show=start->theFlight;
        std::cout <<"│"<<std::setw(8)<<show.terminus<<" "<<std::setw(9)<<weekday[show.day]<<" "<<std::setw(8)<<show.flightNum
                  <<" "<<std::setw(8)<<show.thePlane.planeNum<<" "<<std::setw(12)<<(double)(show.leftSite[0])/show.thePlane.busload[0]<<
                  std::setw(12)<<" "<<(double)(show.leftSite[1])/show.thePlane.busload[1]<<" "<<std::setw(12)<<
                  (double)(show.leftSite[2])/show.thePlane.busload[2]<<" "<<std::setw(11)<<(double)(show.leftSite[3])/show.thePlane.busload[3]<<std::endl;
        std::cout <<"└────────┴───────┴────────┴────────┴────────────┴────────────┴────────────┴────────────┘"<<std::endl;
    }
}
void SingleStatistic(){
    linklist* start=recordInMemory;
    std::cout << "请输入要显示的目的地的报表"<<std::endl;
    std::string direction;
    std::cin >> direction;
    if (terminusSearch(direction,start)==NULL){
        std::cout<<"为查找到该地"<<std::endl;
        return;
    };
    std::cout <<"┌────────┬───────┬────────┬────────┬────────────┬────────────┬────────────┬────────────┐  "<<std::endl;
    std::cout <<"│ 目的地 │ 出发日│ 航班号 │ 飞机号 │头等舱余座率│一等舱余座率│普通舱余座率│  总余座率  │"<<std::endl;
    std::cout <<"├────────┼───────┼────────┼────────┼────────────┼────────────┼────────────┼────────────┤"<<std::endl;
    searchAsTerminus(direction);
}
bool exist(std::string terminus,std::vector<std::string> vec){
    for (auto item:vec){
        if(item==terminus)return true;
    }
    return false;
}
void AllStatistic(){
    std::vector<std::string> searchedDirectionList;
    linklist *start=recordInMemory;
    if(start== nullptr){
        std::cout<<"航班记录为空";
    }
    std::cout <<"┌────────┬───────┬────────┬────────┬────────────┬────────────┬────────────┬────────────┐  "<<std::endl;
    std::cout <<"│ 目的地 │ 出发日│ 航班号 │ 飞机号 │头等舱余座率│一等舱余座率│普通舱余座率│ 总余座率   │"<<std::endl;
    std::cout <<"├────────┼───────┼────────┼────────┼────────────┼────────────┼────────────┼────────────┤"<<std::endl;
    while(start!= nullptr){
        if(!exist(start->theFlight.terminus,searchedDirectionList)){
              searchAsTerminus(start->theFlight.terminus);
              searchedDirectionList.push_back(start->theFlight.terminus);
        }
        start=start->next;
    }
    std::cout<<"检索完毕"<<std::endl;
}
void showStatisticMenu() {
    system("clear");
    std::cout << "====== 航班报表统计 ======" << std::endl;
    std::cout << "S. 单一目的地统计" << std::endl;
    std::cout << "A. 全部统计" << std::endl;
    std::cout << "Q. 退出" << std::endl;
    std::cout << "===========================" << std::endl;
}
void Statistic(){
    char choice;
    showStatisticMenu();
    do {
        std::cin >> choice;
        switch (choice) {
            case 'S':
                SingleStatistic();
                break;
            case 'A':
                AllStatistic();
                break;
            case 'Q':
                return;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (true);
}