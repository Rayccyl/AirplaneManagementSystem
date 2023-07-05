//
// Created by 23689 on 2023/7/2.
//
#include <iostream>
#include <sstream>
#include <fstream>
#include "APBS.h"
//TODO 设立新plane信息的时候检查是否已经存在planeID
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
void savePlaneRecord(plane in){
    std::ofstream to("plane.rec",std::ios::app);
    to << in.planeNum<<" "<<in.busload[0]<<" "<<in.busload[1]<<" "<<in.busload[2]
    <<" "<<in.busload[3]<<std::endl;
    to.close();
}
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
linklist* importFlightRecord() {
    std::ifstream file("flight.rec");
    if (file.is_open()) {
        flight value;
        linklist* head = nullptr;
        linklist* tail = nullptr;
        plane record;
        while (file >> value.flightNum >> value.terminus >> value.thePlane.planeNum >> value.leftSite[0]
        >>value.leftSite[1]>>value.leftSite[2]>> value.day) {
            value.leftSite[3]=value.leftSite[0]+value.leftSite[1]+value.leftSite[2];
            record=searchPlaneRecord(value.thePlane.planeNum);
            value.thePlane=record;
            linklist* newNode = new linklist{value, nullptr};

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        file.close();
        std::cout << "读取成功" << std::endl;
        return head;
    } else {
        std::cout << "无法打开文件" << std::endl;
        return nullptr;
    }
}
