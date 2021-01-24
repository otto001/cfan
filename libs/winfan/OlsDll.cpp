#include "pch.h"
#include "OlsDll.h"
#include <ols-api/OlsApiInit.h>
#include <iostream>

HMODULE OlsDll::hModule = NULL;
extern bool OlsDll::isInitialized = false;


bool OlsDll::init()
{
    if (OlsDll::isInitialized) {
        return true;
    }
	BOOL loadedOls = InitOpenLibSys(&OlsDll::hModule);
	if (loadedOls) {
		DWORD status = GetDllStatus();
		std::cout << "Loaded Ols Library with status: " << status << "\n";
		OlsDll::isInitialized = true;
	}
	else {
		DWORD status = GetDllStatus();

		std::cout << "Could not load dll" << status << "\n";
	}
    return false;
}

bool OlsDll::close()
{
	bool res = DeinitOpenLibSys(&OlsDll::hModule);
	return res;
}

bool OlsDll::writeIoPortByte(WORD port, BYTE byte)
{
	bool res = WriteIoPortByteEx(port, byte);
	if (!res) {
		std::wcout << L"OlsDll writeIoPort: Could not write to port" << port;
	}
	return res;
}

bool OlsDll::readIoPortByte(WORD port, BYTE* value)
{
	bool res = ReadIoPortByteEx(port, value);
	if (!res) {
		std::wcout << L"OlsDll readIoPort: Could not read from port" << port;
	}
	return res;
}

bool OlsDll::writeIoPortWord(WORD port, WORD word)
{
	bool res = WriteIoPortWordEx(port, word);
	if (!res) {
		std::wcout << L"OlsDll writeIoPort: Could not write to port" << port;
	}
	return res;
}

bool OlsDll::readIoPortWord(WORD port, WORD* value)
{
	bool res = ReadIoPortWordEx(port, value);
	if (!res) {
		std::wcout << L"OlsDll readIoPort: Could not read from port" << port;
	}
	return res;
}

