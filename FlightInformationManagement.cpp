#include <iostream>
#include "CDRU.h"
void FlightInformationManagementMenu(){
    system("clear");
    std::cout << "======= 基本信息管理 =======" << std::endl;
    std::cout << "C. 航班输入追加" << std::endl;
    std::cout << "D. 删除航班记录" << std::endl;
    std::cout << "R. 显示航班信息" << std::endl;
    std::cout << "U. 修改航班记录" << std::endl;
    std::cout << "S. 航班记录保存" << std::endl;
    std::cout << "Q. 返回上级菜单" << std::endl;
    std::cout << "==========================" << std::endl;
}
void FlightInformationManagement(){
    char choice=0;
    do {
        FlightInformationManagementMenu();
        std::cin.clear();
        std::cin >> choice;

        switch (choice) {
            case 'C':
                addFlightRecord();
                break;
            case 'D':
                removeFlightRecord();
                break;
            case 'R':
                readFlightRecord();
                break;
            case 'U':
                updateFlightRecord();
                break;
            case 'S':
                saveFlightRecord();
                break;
            case 'Q':
                return;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (true);
}
