#include "CDRU.h"
#include "mainMune.h"
#include <vector>
void showMenu() {
    system("clear");
    std::cout << "====== 航空客运售票系统 ======" << std::endl;
    std::cout << "1. 基本信息管理" << std::endl;
    std::cout << "2. 订票管理" << std::endl;
    std::cout << "3. 航班统计报表" << std::endl;
    std::cout << "4. 航线查询" << std::endl;
    std::cout << "0. 退出" << std::endl;
    std::cout << "===========================" << std::endl;
    std::cout << "请选择功能：";
}
linklist *recordInMemory=new linklist;
std::vector<passenger> userList;
int main() {
    int choice=0;
    linklist *temp=importFlightRecord();
    if(temp!= nullptr)recordInMemory=temp;
    importPassengerRecord();
    do {

        showMenu();
        std::cin >> choice;
        switch (choice) {
            case 1:
                FlightInformationManagement();
                break;
            case 2:
                LoginMenu();
                break;
            case 3:
                Statistic();
                break;
            case 4:
                readFlightRecord();
                break;
            case 0:
                saveFlightRecord();
                std::cout << "退出程序" << std::endl;
                break;
            default:
                std::cout << "无效的选择，请重新选择" << std::endl;
                break;
        }
    } while (choice != 0);

    return 0;
}

