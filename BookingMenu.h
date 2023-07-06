//
// Created by 23689 on 2023/7/3.
//

#ifndef APBS_BOOKINGMENU_H
#define APBS_BOOKINGMENU_H
#include "APBS.h"
bool Register();
bool Login();
passenger getUser(std::string id);
void BookingMenu(std::string id);
passenger BookTicket(passenger user);
passenger getRecord(passenger user);
void MyRecord(passenger user);
void PrintTicket(passenger user);
void refund(passenger user);
#endif //APBS_BOOKINGMENU_H
