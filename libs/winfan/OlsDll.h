#pragma once
#include <windows.h>


namespace OlsDll {
	bool init();
	bool close();
	bool writeIoPortByte(WORD port, BYTE byte);
	bool readIoPortByte(WORD port, BYTE* value);

	bool writeIoPortWord(WORD port, WORD word);
	bool readIoPortWord(WORD port, WORD* value);

	extern HMODULE hModule;
	extern bool isInitialized;
};


