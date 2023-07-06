#include <fstream>
#include <sstream>
#include <vector>
#include "APBS.h"
#include "CDRU.h"
extern std::vector<passenger> userList;
extern linklist* recordInMemory;
siteList* newRecord(siteList* root,flight item,int siteType);
void savePlaneRecord(plane in){
    std::ofstream to("plane.rec",std::ios::app);
    to << in.planeNum<<" "<<in.busload[0]<<" "<<in.busload[1]<<" "<<in.busload[2]
       <<" "<<in.busload[3]<<std::endl;
    to.close();
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
void removeTicketRecordInFile(site toRemove){
    std::ifstream old("ticket.rec");
    std::ofstream neo("refundTemp.rec");
    if (old && neo) {
        std::string line;
        while (std::getline(old, line)) {
            // 使用流输入读取记录主键
            std::istringstream iss(line);
            std::string id;
            int flightNum;
            int siteType;
            if (iss >> id >> flightNum >> siteType) {
                if (toRemove.theFlight.flightNum == flightNum && toRemove.level == siteType) {
                    continue;
                }
            }
            // 将记录写入输出文件
            neo << line << std::endl;
        }
        old.close();
        neo.close();
        std::remove("ticket.rec");
        std::rename("refundTemp.rec", "ticket.rec");
        std::cout << "记录已成功删除。" << std::endl;
    }else {
        std::cout << "无法打开输入文件或输出文件。" << std::endl;
    }
}
void saveFlightRecord(){
    extern linklist* recordInMemory;
    std::ofstream file("flight.rec");

    if (file.is_open()) {
        linklist * current = recordInMemory;
        recordInMemory->theFlight.terminus="empty";
        flight import;
        while (current != nullptr) {
            import=current->theFlight;
            file << import.flightNum<<" "<<import.terminus<<" "
                 <<import.thePlane.planeNum<<" "<<import.leftSite[0]<<" "<<
                 import.leftSite[1]<<" "<<import.leftSite[2]<<
                 " "<<import.day<<std::endl;
            current = current->next;
        }

        file.close();
        std::cout << "保存成功" << std::endl;
    } else {
        std::cout << "无法打开文件 保存失败" << std::endl;
    }
}
void importPassengerRecord(){
    std::ifstream file("passenger.rec",std::ios::binary);
//TODO 目前单输进一张链顺序表 内存放不下 且未经排序 不合理
    if (file.is_open()) {
        passenger newRecord;
        while (file >> newRecord.id>>newRecord.name>>newRecord.password) {
            userList.push_back(newRecord);
        }
        file.close();
    } else {
        std::cout << "无法打开文件" << std::endl;
        return;
    }
}
void savePassengerRecord(){
    std::ofstream file("passenger.rec");
    if(!file.is_open()){
        std::cout<<"无法打开文件 保存失败"<<std::endl;
        return;
    }
    for (const auto& user : userList) {
        file << user.id << " "<< user.name <<" "<<user.password <<std::endl;
    }
    file.close();
}
void saveUsersTicket(passenger user){
    std::ofstream to("ticket.rec",std::ios::app);
    std::string id=user.id;
    siteList* p=user.usersSiteList;
    if(p== nullptr){
        std::cout<<"您尚未购票"<<std::endl;
        return;
    }
    while (p->next != nullptr){
        p=p->next;
    }
    to << id <<" "<<p->item.theFlight.flightNum<<" "<<p->item.level<<std::endl;

}
passenger getRecord(passenger user){
    linklist *start=recordInMemory;
    linklist *change= nullptr;
    std::ifstream from("ticket.rec");
    site in;
    std::string id;
    int flightNum=0;
    int siteType=0;
    passenger records;
    while(from>>id){
        if(id==user.id){
            from>>flightNum>>siteType;
            change=flightNumSearch(flightNum,start);
            if(change== nullptr){
                std::cout<<"读取完毕"<<std::endl;
                return user;
            }
            change=change->next;
            user.usersSiteList=newRecord(user.usersSiteList, change->theFlight,siteType);
        }
        else{
            from>>flightNum>>siteType;
        }
    }
    return user;
}