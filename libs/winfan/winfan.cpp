//
// Created by ludwig on 23.01.2021.
//

#include "pch.h"
#include "include/winfan/winfan.h"


#include <iostream>

#include <iostream>
#include "OlsDll.h"
#include "Service.h"
#include "lpcIo/LpcIo.h"
#include "superIo/SmBios.h"
#define DRIVER_NAME "WinRing0_1_2_0"
#define DRIVER_NAME_W L"WinRing0_1_2_0"


SmBios* smBios;


void loadDriver() {
//    auto driverFile = new TCHAR[200];
//    strcpy_s(driverFile, 200, R"(C:\Users\ludwig\Documents\GitHub\cfan\drivers\WinRing0x64.sys)");
//    auto driverName = new TCHAR[200];
//    strcpy_s(driverName, 200, DRIVER_NAME);
//    CService service(driverFile, driverName, driverName, SERVICE_DEMAND_START);
//
//
//    auto result = service.CreateSvc();
//    if (result == SVC_OK) {
//        result = service.StartSvc();
//
//        if (result == SVC_OK) {
//            std::cout << "Started " << DRIVER_NAME << " service." << std::endl;
//
//
//        } else {
//            auto error = GetLastError();
//            if (error == 1056) {
//                std::cout << "Failed to start " << DRIVER_NAME << " service. Error 1056. Stopping service and retrying..." <<  std::endl;
//
//                service.StopSvc(true);
//
//                result = service.StartSvc();
//                if (result == SVC_OK) {
//                    std::cout << "Started " << DRIVER_NAME << " service." << std::endl;
//                }
//            }
//        }
//    }
//    else {
//        std::cerr << "Failed to create " << DRIVER_NAME << " service." << std::endl;
//    }
    return;
}

bool WinFan::init() {
    OlsDll::init();
    LpcIo::isaBusMutexOpen();
    smBios = new SmBios();
    return true;
}
