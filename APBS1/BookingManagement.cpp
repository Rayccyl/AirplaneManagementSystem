//
// Created by 23689 on 2023/7/1.
//
#include "BookingMenu.h"
#include "CDRU.h"

void showLoginMenu(){
    system("clear");
    std::cout << "======= 订票管理 =======" << std::endl;
    std::cout << "R. 旅客注册" << std::endl;
    std::cout << "L. 旅客登录" << std::endl;
    std::cout << "Q. 返回上级菜单" << std::endl;
    std::cout << "==========================" << std::endl;
}
void LoginMenu(){
    char choice=0;
    showLoginMenu();
    do {
        std::cin >> choice;
        switch (choice) {
            case 'R':
                if(Register()){
                    showLoginMenu();
                };
                break;
            case 'L':
                if(Login()){
                    showLoginMenu();
                };
                break;
            case 'Q':
                return;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (true);
}
void showBookingMenu(passenger user){
    std::cout << "=============== 订票管理 ==============" << std::endl;
    std::cout << "用户 ： "<< user.name<<std::endl;
    std::cout << "M. 我的记录" << std::endl;
    std::cout << "B. 购票" << std::endl;
    std::cout << "R. 退票"<<std::endl;
    std::cout << "P. 机票打印" << std::endl;
    std::cout << "S. 查询航班信息" << std::endl;
    std::cout << "L. 登出" << std::endl;
    std::cout << "======================================" << std::endl;
}
//TODO 目前票务信息还不能删
void BookingMenu(std::string id){
    passenger user= getUser(id);
    user= getRecord(user);
    char choice=0;
    do {
        showBookingMenu(user);
        std::cin.clear();
        std::cin >> choice;
        switch (choice) {
            case 'M':
                system("clear");
                MyRecord(user);
                break;
            case 'B':
                user=BookTicket(user);
                system("clear");
                break;
            case 'P':
                system("clear");
                PrintTicket(user);
                break;
            case 'S':
                readFlightRecord();
                system("clear");
                break;
            case 'R':
                refund(user);
                break;
            case 'L':
                return;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (true);
}
