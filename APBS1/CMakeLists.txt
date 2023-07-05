cmake_minimum_required(VERSION 3.25)
project(APBS)

set(CMAKE_CXX_STANDARD 17)

add_executable(APBS main.cpp addFlightRecord.cpp
        FlightInformationManagement.cpp searchFlightRecord.cpp
        removeFlightRecord.cpp CDRU.h readFlightRecord.cpp
        saveFlightRecord.cpp updateFlightRecord.cpp TicketBooking.cpp
        BookingManagement.cpp BookingMenu.h APBS.h BookingCore.cpp statistic.cpp)
