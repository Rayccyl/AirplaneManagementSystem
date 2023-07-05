//
// Created by 23689 on 2023/7/2.
//
#include <iostream>
#include <sstream>
#include "APBS.h"
//所谓返回linklist 实际上只是那个结点
linklist* positionSearch(int n,linklist* start){
    //从start开始 第n个结点 start是第一个结点 返回找到的结点的前继 输入节点需要是之前查找的前置或者头节点
    if(n<1) return nullptr;
    if(n==1)return start;
    linklist* find=start;
    linklist* prior=find;
    int times=1;
    if(find->next!= nullptr)find=find->next;
    else{return nullptr;}
    while(times<n){
        if(find->next!= nullptr)find=find->next;
        else{return nullptr;}
        prior=prior->next;
        times++;
    }
    return prior;
}
linklist* terminusSearch(std::string terminusName,linklist* start){
    linklist* find=start;
    if(find== nullptr)return nullptr;
    while (true){
        if(find->next== nullptr)return nullptr;
        find=find->next;
        if(find->theFlight.terminus==terminusName) return find;

    }
}
linklist* flightNumSearch(int num,linklist* start){
    linklist* find=start;
    linklist* prior=find;
    while (true){
        if(find->next== nullptr)return nullptr;
        find=find->next;
        if(find->theFlight.flightNum==num)return prior;
        prior=prior->next;
    }
}
linklist* planeNumSearch(int num,linklist* start){
    linklist* find=start;
    linklist* prior=find;
    while (true){
        if(find->next== nullptr)return nullptr;
        find=find->next;
        if(find->theFlight.thePlane.planeNum==num)return prior;
        prior=prior->next;
    }
}
linklist* loadNumSearch(int num,linklist* start){
    linklist* find=start;
    linklist* prior=find;
    while (true){
        if(find->next== nullptr)return nullptr;
        find=find->next;
        if(find->theFlight.thePlane.busload[3]==num)return prior;
        prior=prior->next;
    }
}
linklist* daySearch(int day,linklist* start){
    linklist* find=start;
    linklist* prior=find;
    while (true){
        if(find->next== nullptr)return nullptr;
        find=find->next;
        if(find->theFlight.day==day)return prior;
        prior=prior->next;
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