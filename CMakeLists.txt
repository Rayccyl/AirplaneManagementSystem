cmake_minimum_required(VERSION 3.25)
project(APBS)

set(CMAKE_CXX_STANDARD 17)

add_executable(APBS main.cpp
        FlightInformationManagement.cpp searchRecord.cpp
        CDRU.h readFlightRecord.cpp
        TicketBooking.cpp
        BookingManagement.cpp BookingMenu.h APBS.h BookingCore.cpp statistic.cpp fileReadAndWrite.cpp fileIO.h flightADRU.cpp)
