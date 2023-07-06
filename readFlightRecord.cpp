//
// Created by 23689 on 2023/7/2.
//
#include "CDRU.h"
#include "show.h"
siteList* newRecord(siteList* root,flight item,int siteType);
void showFlightInformationMenu(){
    system("clear");
    std::cout << "======= 航班信息查询 =======" << std::endl;
    std::cout << "1. 按位查询" << std::endl;
    std::cout << "2. 按目的地查询" << std::endl;
    std::cout << "3. 按航班号查询" << std::endl;
    std::cout << "4. 按飞机号查询" << std::endl;
    std::cout << "5. 按载荷查询" << std::endl;
    std::cout << "6. 按出发日查询" << std::endl;
    std::cout << "7. 按余票查询" << std::endl;
    std::cout << "8. 显示所有" << std::endl;
    std::cout << "0. 返回上级菜单" << std::endl;
    std::cout << "==========================" << std::endl;
}
void readFlightRecord(){
    int option=0;
    showFlightInformationMenu();
    do {
        std::cin >> option;
        switch (option) {
            case 1:showAsPosition();
                break;
            case 2:showAsTerminus();
                break;
            case 3:showAsFlightNum();
                break;
            case 4:showAsPlaneNum();
                break;
            case 5:showAsBusload();
                break;
            case 6:showAsDay();
                break;
            case 7:showAsLeftTicket();
                break;
            case 8:showAll();
                break;
            case 0:
                return;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (true);
}