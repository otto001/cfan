#pragma once
#include <vector>
#include "Device.h"
#include "MainBoard.h"
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

class SmBios
{
public:
    void init();
    std::string report();
private:
    bool getRaw(RawSMBIOSData**);
    void parseRaw(RawSMBIOSData*);

    std::vector<Device*> devices;
    MainBoard* mainBoard;
public:
    MainBoard *getMainBoard() const;
};

