//
// Created by 23689 on 2023/7/2.
//
#include <iostream>
#include <sstream>
#include <fstream>
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
plane searchPlaneRecord(int id){
    std::ifstream planeRecord("plane.rec");
    plane toReturn{0,{0,0,0}};
    if(id==0)return toReturn;
    while (planeRecord>>toReturn.planeNum){
        planeRecord>>toReturn.busload[0]>>toReturn.busload[1]>>
                   toReturn.busload[2]>>toReturn.busload[3];
        if(toReturn.planeNum==id){
            return toReturn;
        }
    }
    return toReturn;
}