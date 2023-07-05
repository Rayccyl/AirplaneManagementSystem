//
// Created by 23689 on 2023/7/2.
//
#include "CDRU.h"
void updateFlightRecord(){
    extern linklist* recordInMemory;
    linklist* start=recordInMemory;
    int num=0;
    char YN;
    linklist* prior;
    flight change=start->theFlight;
    flight turnTo;
    while(true){
        std::cout<<"请输入要修改的航班号 输入0返回上级菜单"<<std::endl;
        std::cin>>num;
        if(num==0)return;
        if ((start=flightNumSearch(num,start))!=nullptr){
            change=start->next->theFlight;
            std::cout<<weekday[change.day]<< "开往" << change.terminus <<"的航班"<<change.flightNum<<"  ";
            std::cout<<"请输出新的航班号 目的地 飞机号 0123载荷 出发日"<<std::endl;
            std::cin>>turnTo.flightNum>>turnTo.terminus>>turnTo.thePlane.planeNum>>
                    turnTo.thePlane.busload[0]>>turnTo.thePlane.busload[1]>>turnTo.thePlane.busload[2]>>
                    turnTo.day;
            turnTo.thePlane.busload[3]=turnTo.thePlane.busload[2]+turnTo.thePlane.busload[1]+turnTo.thePlane.busload[0];
            std::cout<<"确认修改本条记录吗 Y是N否\n";
            std::cin>>YN;
            if(YN=='N')continue;
            else if(YN=='Y'){
                turnTo.leftSite[3]=turnTo.thePlane.busload[3];
                turnTo.leftSite[2]=turnTo.thePlane.busload[2];
                turnTo.leftSite[1]=turnTo.thePlane.busload[1];
                turnTo.leftSite[0]=turnTo.thePlane.busload[0];
                start->next->theFlight=turnTo;
            }
            else{
                std::cout<<"非法字符 请重新输入"<<std::endl;
            }
        }else{
            std::cout<<"抱歉 未找到您所指定的航班"<<std::endl;
        }
    }

}