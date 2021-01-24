#include "../pch.h"
#include "LpcIo.h"
#include "../defines.h"
#include <iostream>
#include "../OlsDll.h"
#include "../Chips.h"
#include <chrono>
#include <thread>


#define ISA_BUS_MUTEX_NAME  L"Global\\Access_ISABUS.HTP.Method"

HANDLE LpcIo::isaBusMutex = NULL;


const std::vector<LpcIoPort*> LpcIo::lpcIoPorts = {new LpcIoPort(0x2E, 0x2F), new LpcIoPort(0x4E, 0x4F)};

void LpcIo::init()
{
	isaBusMutexOpen();
	
}

void LpcIo::detect()
{
	chip = Chip::Unknown;
	ldn = LDN::Unknown;
	if (isaBusMutexWait(100)) {
		for (auto port : lpcIoPorts) {
			detectWinboundFintek(port);
			if (chip != Chip::Unknown) {
				chipPort = port;
				break;
			}
		}
		isaBusMutexRelease();
	}
}

bool LpcIo::isaBusMutexWait(int millisecondsTimeout) {
	if (isaBusMutex == NULL) {
		return false;
	}
	
	DWORD res = WaitForSingleObject(isaBusMutex, millisecondsTimeout);
	return res == WAIT_OBJECT_0;
}

bool LpcIo::isaBusMutexRelease() {
	if (isaBusMutex == NULL) {
		return false;
	}
	return ReleaseMutex(isaBusMutex);
}

bool LpcIo::isaBusMutexOpen()
{
	if (isaBusMutex != NULL) {
		return true;
	}
	isaBusMutex = CreateMutex(NULL, FALSE, ISA_BUS_MUTEX_NAME);
	if (isaBusMutex != NULL) {
		std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex was created\n";
		return true;
	}
	else {
		isaBusMutex = OpenMutex(SYNCHRONIZE, FALSE, ISA_BUS_MUTEX_NAME);
		if (isaBusMutex != NULL) {
			std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex could not be opened/created\n";
		}
		else {
			std::wcout << ISA_BUS_MUTEX_NAME << L" Mutex was opened\n";
			return true;

		}
	}
	return false;
}

bool LpcIo::isaBusMutexClose()
{
	bool res = CloseHandle(isaBusMutex);
	if (res) {
		isaBusMutex = NULL;
	}
	return res;
}

void LpcIo::detectWinboundFintek(const LpcIoPort* port)
{
	port->detectWinboundFintekEnter();

	chipId = port->readRegister(CHIP_ID_REGISTER);
	chipRevision = port->readRegister(CHIP_REVISION_REGISTER);
	
	switch (chipId) {
		case 0xC8: {
			switch (chipRevision) {
				case 0x03:
					chip = Chip::NCT6791D;
					ldn = LDN::WINBOND_NUVOTON_HARDWARE_MONITOR_LDN;
				default:
					break;
			}
		}
		case 0xD4: {
			switch (chipRevision) {
				case 0x2b:
					chip = Chip::NCT6798D;
					ldn = LDN::WINBOND_NUVOTON_HARDWARE_MONITOR_LDN;
				default:
					break;
			}
		}

		default:
			break;
	}

	if (chip == Chip::Unknown) {
		std::cout << "Unknown Chip" << std::endl;
		return;
	}
	port->selectLdn(ldn);
	uint16_t address = port->readRegisterWord(BASE_ADDRESS_REGISTER);

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	uint16_t addressVerify = port->readRegisterWord(BASE_ADDRESS_REGISTER);


	uint16_t vendorID = port->readRegisterWord(FINTEK_VENDOR_ID_REGISTER);
	chipPortAddress = address;
	port->detectWinboundFintekExit();
	std::cout << "SuperIO Chip Detected" << std::endl;
}






