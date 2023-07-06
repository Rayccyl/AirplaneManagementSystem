//
// Created by 23689 on 2023/7/2.
//

#ifndef APBS_CDRU_H
#define APBS_CDRU_H
#include "APBS.h"
plane searchPlaneRecord(int id);
void addFlightRecord();
void removeFlightRecord();
linklist* positionSearch(int n,linklist* start);
linklist* terminusSearch(std::string terminusName,linklist* start);
linklist* flightNumSearch(int num,linklist* start);
linklist* planeNumSearch(int num,linklist* start);
linklist* loadNumSearch(int num,linklist* start);
linklist* daySearch(int day,linklist* start);
void readFlightRecord();
void saveFlightRecord();
void updateFlightRecord();
#endif //APBS_CDRU_H