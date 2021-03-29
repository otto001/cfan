#include "pch.h"
#include "OlsDll.h"
#include <ols-api/OlsApiInit.h>
#include <iostream>


#define ISA_BUS_MUTEX_NAME  L"Global\\Access_ISABUS.HTP.Method"
#define PCI_BUS_MUTEX_NAME L"Global\\Access_PCI"


HMODULE OlsDll::hModuleDll = nullptr;
HANDLE OlsDll::isaBusMutex = nullptr;
HANDLE OlsDll::pciBusMutex = nullptr;
extern bool OlsDll::isInitialized = false;


bool OlsDll::init()
{
    if (OlsDll::isInitialized) {
        return true;
    }
	BOOL loadedOls = InitOpenLibSys(&OlsDll::hModuleDll);
	if (loadedOls) {
		DWORD status = GetDllStatus();
		std::cout << "Loaded Ols Library with status: " << status << "\n";
		OlsDll::isInitialized = true;
	}
	else {
		DWORD status = GetDllStatus();

		std::cout << "Could not load dll" << status << "\n";
	}
    OlsDll::isaBusMutexOpen();
    OlsDll::pciBusMutexOpen();
    return OlsDll::isInitialized;
}

bool OlsDll::close() {
	bool res = DeinitOpenLibSys(&OlsDll::hModuleDll);
    OlsDll::isaBusMutexClose();
    OlsDll::pciBusMutexClose();
    return res;
}

bool OlsDll::writeIoPortByte(WORD port, BYTE byte)
{
	bool res = WriteIoPortByteEx(port, byte);
	if (!res) {
		std::cerr << "OlsDll writeIoPort: Could not write to port " << port << std::endl;
	}
	return res;
}

bool OlsDll::readIoPortByte(WORD port, BYTE* value)
{
	bool res = ReadIoPortByteEx(port, value);
	if (!res) {
		std::cerr << L"OlsDll readIoPort: Could not read from port " << port << std::endl;
	}
	return res;
}

bool OlsDll::writeIoPortWord(WORD port, WORD word)
{
	bool res = WriteIoPortWordEx(port, word);
	if (!res) {
		std::cerr << L"OlsDll writeIoPort: Could not write to port " << port << std::endl;
	}
	return res;
}

bool OlsDll::readIoPortWord(WORD port, WORD* value)
{
	bool res = ReadIoPortWordEx(port, value);
	if (!res) {
		std::cerr << L"OlsDll readIoPort: Could not read from port " << port << std::endl;
	}
	return res;
}


bool OlsDll::writePciConfigDword(DWORD address, BYTE reg, DWORD value) {
    bool res = WritePciConfigDwordEx(address, reg, value);
    if (!res) {
        std::cerr << L"OlsDll writeIoPort: Could not write to port " << address << std::endl;
    }
    return res;
}

bool OlsDll::readPciConfigDword(DWORD address, BYTE reg, DWORD* value) {
    bool res = ReadPciConfigDwordEx(address, reg, value);
    if (!res) {
        std::cerr << L"OlsDll readIoPort: Could not read from port " << address << std::endl;
    }
    return res;
}






bool OlsDll::isaBusMutexWait(int millisecondsTimeout) {
    if (isaBusMutex == nullptr) {
        return false;
    }

    DWORD res = WaitForSingleObject(isaBusMutex, millisecondsTimeout);
    return res == WAIT_OBJECT_0;
}

bool OlsDll::isaBusMutexRelease() {
    if (isaBusMutex == nullptr) {
        return false;
    }
    return ReleaseMutex(isaBusMutex);
}

bool OlsDll::isaBusMutexOpen()
{
    if (isaBusMutex != nullptr) {
        return true;
    }
    isaBusMutex = CreateMutex(nullptr, FALSE, ISA_BUS_MUTEX_NAME);
    if (isaBusMutex != nullptr) {
        std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex was created\n";
        return true;
    }
    else {
        isaBusMutex = OpenMutex(SYNCHRONIZE, FALSE, ISA_BUS_MUTEX_NAME);
        if (isaBusMutex != nullptr) {
            std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex could not be opened/created\n";
        }
        else {
            std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex was opened\n";
            return true;

        }
    }
    return false;
}

bool OlsDll::isaBusMutexClose()
{
    bool res = CloseHandle(isaBusMutex);
    if (res) {
        isaBusMutex = nullptr;
    }
    return res;
}



bool OlsDll::pciBusMutexWait(int millisecondsTimeout) {
    if (pciBusMutex == nullptr) {
        return false;
    }

    DWORD res = WaitForSingleObject(pciBusMutex, millisecondsTimeout);
    return res == WAIT_OBJECT_0;
}

bool OlsDll::pciBusMutexRelease() {
    if (pciBusMutex == nullptr) {
        return false;
    }
    return ReleaseMutex(pciBusMutex);
}

bool OlsDll::pciBusMutexOpen()
{
    if (pciBusMutex != nullptr) {
        return true;
    }
    pciBusMutex = CreateMutex(nullptr, FALSE, PCI_BUS_MUTEX_NAME);
    if (pciBusMutex != nullptr) {
        std::wcout << PCI_BUS_MUTEX_NAME << L" Mutex was created\n";
        return true;
    }
    else {
        pciBusMutex = OpenMutex(SYNCHRONIZE, FALSE, PCI_BUS_MUTEX_NAME);
        if (pciBusMutex != nullptr) {
            std::wcout << PCI_BUS_MUTEX_NAME << L" Mutex could not be opened/created\n";
        }
        else {
            std::wcout << PCI_BUS_MUTEX_NAME << L" Mutex was opened\n";
            return true;

        }
    }
    return false;
}

bool OlsDll::pciBusMutexClose()
{
    bool res = CloseHandle(pciBusMutex);
    if (res) {
        pciBusMutex = nullptr;
    }
    return res;
}
