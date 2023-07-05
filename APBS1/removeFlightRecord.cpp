//
// Created by 23689 on 2023/7/2.
//
#include <iostream>
#include "CDRU.h"
//TODO 索引查找
void removeFlightRecord(){
    extern linklist *recordInMemory;
    flight show;
    char YN;
    std::cout<<"请输入要删除的航班号 输入0返回上级菜单"<<std::endl;
    int toDelNum;
    linklist *priorDel;
    while(true){
        std::cin>>toDelNum;
        if(toDelNum==0)return;
        if((priorDel= flightNumSearch(toDelNum, recordInMemory)) != nullptr){
            show=priorDel->next->theFlight;
            std::cout<<weekday[show.day]<< "开往" << show.terminus <<"的航班"<<show.flightNum<<"  ";
            std::cout<<"确认删除本条记录吗 Y是N否\n";
            std::cin>>YN;
            if(YN=='N')continue;
            else if(YN=='Y'){
                if(priorDel->next->next== nullptr) {
                    delete priorDel->next;
                    priorDel->next= nullptr;
                }
                else{
                    priorDel->next=priorDel->next->next;
                }
            }
            else{
                std::cout<<"非法字符 请重新输入"<<std::endl;
            }
        }else{
            std::cout<<"抱歉 未找到您所指定的航班"<<std::endl;
            return;
        }
    }

}