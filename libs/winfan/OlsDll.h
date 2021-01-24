#pragma once
#include <windows.h>


namespace OlsDll {
	bool init();
	bool close();
	bool writeIoPortByte(WORD port, BYTE byte);
	bool readIoPortByte(WORD port, BYTE* value);

	bool writeIoPortWord(WORD port, WORD word);
	bool readIoPortWord(WORD port, WORD* value);


    bool writePciConfigDword(DWORD address, BYTE reg, DWORD value);
    bool readPciConfigDword(DWORD address, BYTE reg, DWORD* value);

	extern HMODULE hModuleDll;
	extern bool isInitialized;


    extern HANDLE isaBusMutex;
    bool isaBusMutexWait(int millisecondsTimeout);
    bool isaBusMutexRelease();
    bool isaBusMutexOpen();
    bool isaBusMutexClose();

    extern HANDLE pciBusMutex;
    bool pciBusMutexWait(int millisecondsTimeout);
    bool pciBusMutexRelease();
    bool pciBusMutexOpen();
    bool pciBusMutexClose();
};


