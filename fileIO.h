//
// Created by 23689 on 2023/7/6.
//
#include "APBS.h"
#ifndef APBS_FILEIO_H
#define APBS_FILEIO_H
void savePlaneRecord(plane in);
void removeTicketRecordInFile(site toRemove);
linklist* importFlightRecord();
void saveFlightRecord();
void savePassengerRecord();
void importPassengerRecord();
void saveUsersTicket(passenger user);
#endif //APBS_FILEIO_H
