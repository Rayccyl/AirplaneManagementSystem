//
// Created by 23689 on 2023/7/2.
//
#include <fstream>
#include "APBS.h"
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