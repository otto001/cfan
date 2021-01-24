#pragma once
#include <vector>
#include "Device.h"
#include "mainboard/MainBoard.h"
#include "cpu/CPU.h"
#include <Windows.h>


struct RawSMBIOSData
{
    BYTE    used20CallingMethod;
    BYTE    majorVersion;
    BYTE    minorVersion;
    BYTE    dmiRevision;
    DWORD   length;
    BYTE    raw[];
};

class Devices
{
public:
    void init();
    std::string report();
private:
    bool getRawSMBios(RawSMBIOSData **data);
    void parseRawSMBios(RawSMBIOSData *data);

    std::vector<Device*> devices;
    MainBoard* mainBoard;
    CPU* cpu;
public:
    CPU *getCpu() const;

public:
    MainBoard *getMainBoard() const;
};

