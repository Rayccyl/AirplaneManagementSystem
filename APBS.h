//
// Created by 23689 on 2023/7/2.
//

#ifndef APBS_APBS_H
#define APBS_APBS_H

#include <iostream>
typedef struct plane{
    int planeNum=0;
    int busload[4]={};
}plane;
typedef struct flight{
    std::string terminus;
    int flightNum=0;
    plane thePlane;
    int day=0;
    int leftSite[4]={};
}flight;
typedef struct Linklist{
    flight theFlight;
    Linklist *next= nullptr;
}linklist;
const std::string weekday[]={"","周一","周二","周三","周四","周五","周六","周日"};
const std::string siteLevel[]={"特等座","一等座","经济座"};
typedef struct site{
    flight theFlight;
    int level;
}site;
typedef struct siteList{
    site item;
    siteList* next;
}siteList;
typedef struct passenger{
    siteList * usersSiteList= nullptr;
    std::string name;
    std::string id;
    std::string password;
}passenger;
#endif //APBS_APBS_H
