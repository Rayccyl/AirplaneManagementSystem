//
// Created by 23689 on 2023/7/3.
//
#include "BookingMenu.h"
#include "show.h"
#include <fstream>
#include <sstream>

extern linklist* recordInMemory;
siteList* newRecord(siteList* root,flight item,int siteType){
    if(root== nullptr){
        root=new siteList ;
        root->item.theFlight=item;
        root->item.level=siteType;
        root->next= nullptr;
        return root;
    }
    siteList* head=root;
    while(root->next!= nullptr){
        root=root->next;
    }
    root->next=new siteList;
    root=root->next;
    root->item.theFlight=item;
    root->item.level=siteType;
    root->next= nullptr;
    return head;
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

passenger BookTicket(passenger user){
    extern linklist* recordInMemory;
    linklist *start=recordInMemory;
    linklist *pLinklist=start;
    flight show;
    std::string terminus;
    std::cout<<"您的目的地是？";
    std::cin.clear();
    std::cin>>terminus;
    while(true){
        show = pLinklist->theFlight;
        if(show.terminus==terminus){
            std::cout<<"航班"<<show.flightNum<<" 每"<<weekday[show.day]<<"开往"<<show.terminus<<"\t飞机号"<<show.thePlane.planeNum
                     <<"\t目前余座"<<show.leftSite[3]<<std::endl;
            std::cout<<"其中 特等座"<<show.leftSite[0]<<"席 一等座"<<show.leftSite[1]<<"席 二等座"<<show.leftSite[2]<<"席";
        }
        if(pLinklist->next == nullptr){std::cout << "查找完毕\n";
            break;}
        pLinklist=pLinklist->next;
    }
    std::cout<<"您要订购的航班号是 按0退出";
    int num;
    std::cin>>num;
    if(num==0)return user;
    linklist* prior=flightNumSearch(num,start);
    if(prior== nullptr){
        std::cout<<"检索不到此航班"<<std::endl;
        return user;
    }
    flight toBook=prior->next->theFlight;
    int siteType;
    char YN;
    while (true){
        std::cout<<"您要订购的席型是 0特等座 1一等座 2二等座,输入其他任意数退出"<<std::endl;
        siteType=3;
        std::cin.clear();
        std::cin>>siteType;
        if(siteType==0||siteType==1||siteType==2){
            if(siteType==0&&toBook.leftSite[siteType]<=0){std::cout<<"特等座已购满";
                continue;}
            if(siteType==1&&toBook.leftSite[siteType]<=0){std::cout<<"一等座已购满";
                continue;}
            if(siteType==2&&toBook.leftSite[siteType]<=0){std::cout<<"二等座已购满";
                continue;}
            std::cout<<user.name<<user.id<<"订购"<<weekday[toBook.day]<<"飞往"<<toBook.terminus<<
                     "的航班"<<toBook.flightNum<<siteLevel[siteType]<<std::endl;
            std::cout<<"是否确认Y/N"<<std::endl;
            std::cin.clear();
            std::cin>>YN;
            if(YN=='Y'){
                prior->next->theFlight.leftSite[siteType]--;
                prior->next->theFlight.leftSite[3]--;
                //航班记录当前用户乘坐
                //user.userSiteList预计是一个链表 要在给链表开空间的基础上赋值
                user.usersSiteList=newRecord(user.usersSiteList,prior->next->theFlight,siteType);
                saveUsersTicket(user);
                saveFlightRecord();
            }else{
                return user;
            }
        }else{
            return user;
        }
    }
}
void MyRecord(passenger user){
    std::cout<<"============================"<<std::endl;
    std::cout<<user.id<<"        "<<user.name<<std::endl;
    std::cout<<"============================"<<std::endl;
    if(user.usersSiteList== nullptr){
        std::cout<<"未检索到购票记录"<<std::endl;
        return;
    }
    siteList* p=user.usersSiteList;
    site show;
    do{
        show=p->item;
        std::cout<<weekday[show.theFlight.day]<<"乘 "<<show.theFlight.flightNum<<" 号航班 前往"<<
        show.theFlight.terminus<<"\t"<<siteLevel[show.level]<<std::endl;
        p=p->next;
    }while(p!= nullptr);
}
void PrintTicket(passenger user){
    MyRecord(user);
    site show;
    std::cout << "您想打印的机票是(请输入航班号)"<<std::endl;
    int num=0;
    std::cin>>num;
    siteList* p= user.usersSiteList;
    if(p== nullptr){
        std::cout<<"未查找到您的购票记录"<<std::endl;
        return;
    }
    while (p!= nullptr){
        if(p->item.theFlight.flightNum==num){
            std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║                    Ticket                      ║" << std::endl;
            std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
            std::cout << "║ Name:" << user.name << std::endl;
            std::cout << "║ ID:" << user.id << std::endl;
            std::cout << "╔════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║ Destination:  " << p->item.theFlight.terminus<<"                         ║" << std::endl;
            std::cout << "║ Flight:  " << p->item.theFlight.flightNum <<"                              ║" <<std::endl;
            std::cout << "║ Plane:  " << p->item.theFlight.thePlane.planeNum <<"                                  ║"<< std::endl;
            std::cout << "║ Site:  " << siteLevel[p->item.level]<<"                                  ║"<<std::endl;
            std::cout << "╚════════════════════════════════════════════════╝" << std::endl;
            std::ofstream to("yourTicket.txt");
            to << "╔════════════════════════════════════════════════╗" << std::endl;
            to << "║                    Ticket                                                                             ║" << std::endl;
            to << "╚════════════════════════════════════════════════╝" << std::endl;
            to << "║ Name:" << user.name << std::endl;
            to << "║ ID:" << user.id << std::endl;
            to << "╔════════════════════════════════════════════════╗" << std::endl;
            to << "║ Destination:  " << p->item.theFlight.terminus<<"                                                                            ║" << std::endl;
            to << "║ Flight:  " << p->item.theFlight.flightNum <<"                                                                                    ║" <<std::endl;
            to << "║ Plane:  " << p->item.theFlight.thePlane.planeNum <<"                                                                                         ║"<< std::endl;
            to << "║ Site:  " << siteLevel[p->item.level]<<"                                                                                          ║"<<std::endl;
            to << "╚════════════════════════════════════════════════╝" << std::endl;

            return;
        }
        p=p->next;
    }
    std::cout<<"为检索到该航班的购票记录";
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
void refund(passenger user){
    if(user.usersSiteList== nullptr){
        std::cout<<"您尚未购票"<<std::endl;
        return;
    }
    siteList* &p=user.usersSiteList;
    std::cout<<"您已购买的航班有"<<std::endl;
    MyRecord(user);
    std::cout << "您想退的机票是(请输入航班号)"<<std::endl;
    int num=0;
    std::cin>>num;
    if (p->item.theFlight.flightNum == num) {
        removeTicketRecordInFile(p->item);
        p->item.theFlight.leftSite[p->item.level]++;
        p->item.theFlight.leftSite[3]++;
        p=p->next;
        return;
        //TODO 外存交互
    }
    while (p->next!= nullptr) {
        if (p->next->item.theFlight.flightNum == num) {
            removeTicketRecordInFile(p->next->item);
            p->next->item.theFlight.leftSite[p->next->item.level]++;
            p->next->item.theFlight.leftSite[3]++;
            p=p->next;
            //TODO 外存交互
            return;
        }
        p=p->next;
    }
    std::cout<<"您未购买此航班"<<std::endl;
}