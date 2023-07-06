//
// Created by 23689 on 2023/7/3.
//
#include <iostream>
#include <fstream>
#include <vector>
#include "fileIO.h"
#include "BookingMenu.h"
extern std::vector<passenger> userList;

std::string idExist(std::string id){
    for (auto user:userList) {
        if(id==user.id){
            return user.password;
        }
    }
    return "";
}
passenger getUser(std::string id){
    passenger empty={nullptr,"",""};
    for (auto user:userList) {
        if(id==user.id){
            return user;
        }
    }
    return empty;
}
bool Register(){
    std::cout<<"请输入您的姓名 身份证号"<<std::endl;
    std:: string name;
    std::string id;
    std::cin>>name>>id;
    if(idExist(id)!=""){
        std::cout<<"该用户已存在 请登录"<<std::endl;
        return false;
    }
    passenger newUser;
    newUser.name=name;
    newUser.id=id;
    std::cout<<"请输入密码";
    //TODO 可以考虑做重复输入确认密码
    std::string password;
    std::cin>>password;
    newUser.password=password;
    std::cout<<"用户"<<name<<id<<","<<"密码"<<password<<"创建成功"<<std::endl;
    userList.push_back(newUser);
    savePassengerRecord();
    //进系统
    system("clear");
    BookingMenu(id);
    return true;
}
bool Login(){
    std::cout<<"请输入您的身份证号";
    std::string id;
    std::string key;
    std::cin>>id;
    if((key=idExist(id))==""){
        std::cout<<"未查找到"<<id<<"的信息"<<std::endl;
        return false;
    }
    std::cout<<"请输入密码";
    std::string password;
    std::cin>>password;
    if(key==password){
        system("clear");
        std::cout<<"密码正确"<<std::endl;
        BookingMenu(id);
        return true;
    }else{
        std::cout<<"密码错误"<<std::endl;
        return false;
    }
}
