#include "../pch.h"
#include <chrono>

#include "SuperIo.h"
#include "NCT6775.h"
#include "../include/winfan/winfan.h"


SuperIo::SuperIo(Chip _chip, uint8_t _revision, uint16_t _port, const LpcIoPort* _lpcPort) : chip(_chip), revision(_revision), port(_port), lpcPort(_lpcPort)
{
}


void SuperIo::timedUpdate(bool force) {
    auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now())
            .time_since_epoch().count();

    if (force || lastUpdate == 0 || now - lastUpdate > WinFan::interval) {
        lastUpdate = now;
        update();
    }

}
