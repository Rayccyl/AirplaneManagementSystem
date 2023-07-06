//
// Created by 23689 on 2023/7/6.
//
#include <fstream>
#include <sstream>
#include "fileIO.h"
#include "CDRU.h"
//TODO 设立新plane信息的时候检查是否已经存在planeID
extern linklist *recordInMemory;
void addFlightRecord(){
    linklist *root=recordInMemory;
    std::cout<<"请输入新增航班信息: 航班号 终点站 飞机号 特等座数 一等座数 二等座数 航班日 ；输入E 终止新增\n";
    std::string recordString;
    bool first= true;
    while (recordInMemory->next!= nullptr){
        recordInMemory=recordInMemory->next;
    }

    while (true){
        std::getline(std::cin,recordString);
        if (recordString.empty()) continue;
        if(recordString.length()==1&&recordString.at(0)=='E') {
            recordInMemory=root ;
            return;
        }
        if(first&&root->next== nullptr){
            recordInMemory->theFlight=flight();
            recordInMemory->next=new linklist ;
            recordInMemory=recordInMemory->next;
        }else{
            recordInMemory->next=new linklist ;
            recordInMemory=recordInMemory->next;
        }
        first= false;
        std::stringstream singleRecord(recordString);
        singleRecord >> recordInMemory->theFlight.flightNum>>recordInMemory->theFlight.terminus
                     >>recordInMemory->theFlight.thePlane.planeNum>>recordInMemory->theFlight.thePlane.busload[0]>>
                     recordInMemory->theFlight.thePlane.busload[1]>>recordInMemory->theFlight.thePlane.busload[2]
                     >>recordInMemory->theFlight.day;
        recordInMemory->theFlight.thePlane.busload[3]=recordInMemory->theFlight.thePlane.busload[0]+
                                                      recordInMemory->theFlight.thePlane.busload[1]+recordInMemory->theFlight.thePlane.busload[2];
        recordInMemory->theFlight.leftSite[3]= recordInMemory->theFlight.thePlane.busload[3];
        recordInMemory->theFlight.leftSite[2]= recordInMemory->theFlight.thePlane.busload[2];
        recordInMemory->theFlight.leftSite[1]= recordInMemory->theFlight.thePlane.busload[1];
        recordInMemory->theFlight.leftSite[0]= recordInMemory->theFlight.thePlane.busload[0];
        savePlaneRecord(recordInMemory->theFlight.thePlane);
    }
}
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
extern linklist *recordInMemory;
void showAsPosition(){
    linklist *start=recordInMemory;
    linklist *prior;
    int n=0;
    std::cout<<"您要查找第几条记录？";
    std::cin>>n;
    if((prior=positionSearch(n,start))== nullptr){
        std::cout<<"查找不到\n";
        return;
    }
    flight show= prior->next->theFlight;
    std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
             <<"\t目前余座"<<show.leftSite[3]<<std::endl;
}
void showAsTerminus(){
    linklist *start=recordInMemory;
    linklist *pLinklist=start;
    flight show;
    std::string terminus;
    std::cout<<"您要查找的目的地是？";
    std::cin.clear();
    std::cin>>terminus;
    while(true){
        show = pLinklist->theFlight;
        if(show.terminus==terminus){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }
        if(pLinklist->next == nullptr){std::cout << "查找完毕\n";
            return;}
        pLinklist=pLinklist->next;
    }

}
void showAsFlightNum(){
    linklist *start=recordInMemory;
    linklist *pLinklist=start;
    int num=0;
    std::cout<<"您要查找的航班号是";
    std::cin>>num;


    while(true){
        flight show= pLinklist->theFlight;
        if(show.flightNum==num){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }
        if(pLinklist->next== nullptr){
            std::cout<<"查找完毕\n";
            return;
        }
        pLinklist=pLinklist->next;
    }

}
void showAsPlaneNum(){
    linklist *start=recordInMemory;
    linklist *pLinklist=start;
    flight show;
    int num;
    std::cout<<"您要查找的飞机号是？";
    std::cin>>num;
    while(true){
        show= pLinklist->theFlight;
        if(num==show.thePlane.planeNum){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }

        if(pLinklist->next == nullptr){
            std::cout<<"查找完毕\n";
            return;
        }
        pLinklist=pLinklist->next;
    }
}
void showAsBusload(){
    linklist *pTraverse=recordInMemory;
    char input[]={};
    flight show;
    int low;int high;
    std::cout<<"您要查找的载荷范围？“100-600”或“-600”或“100-”\n";
    std::cin>>low>>high;
    for(;pTraverse!= nullptr;pTraverse=pTraverse->next){
        show=pTraverse->theFlight;
        if(low<=show.thePlane.busload[3]&&show.thePlane.busload[3]<=high){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }
    }
    //TODO: 目前这个最大值是估算出来的 下一步估计要把链顺序表构造起来 然后完善这个high的默认值
}
void showAsDay(){
    linklist *pTraverse=recordInMemory;
    flight show;
    int low;int high;
    std::cout<<"您要查找的周数？例“1 7”或“4 4”";
    std::cin>>low>>high;
    for(;pTraverse!= nullptr;pTraverse=pTraverse->next){
        show=pTraverse->theFlight;
        if(low<=show.day&&show.day<=high){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }
    }
}
void showAsLeftTicket(){
    linklist *pTraverse=recordInMemory;
    char *input;
    flight show;
    int low;int high;
    std::cout<<"您要查找的余票范围？“100-600”或“-600”或“100-”\n";
    std::cin>>low>>high;
    for(;pTraverse!= nullptr;pTraverse=pTraverse->next){
        show=pTraverse->theFlight;
        if(low<=show.leftSite[3]&&show.leftSite[3]<=high){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
        }
    }
}
void showAll(){
    linklist *pTraverse=recordInMemory->next;
    flight show;
    for(;pTraverse!= nullptr;pTraverse=pTraverse->next){
        show=pTraverse->theFlight;
        std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                 <<"\t目前余座"<<show.leftSite[3]<<std::endl;
    }
};
