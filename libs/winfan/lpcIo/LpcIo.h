#pragma once

#include <synchapi.h>
#include <vector>
#include "LpcIoPort.h"


class LpcIo
{
public:
	void init();
	void detect();

private:
	static HANDLE isaBusMutex;
	Chip chip;
	LDN ldn;
	uint8_t chipId;
	uint8_t chipRevision;
	LpcIoPort* chipPort;
	uint16_t chipPortAddress;

public:
	inline Chip getChip() { return chip; }
	inline uint8_t getChipId() { return chipId; }
	inline uint8_t getChipRevision() { return chipRevision; }
	inline LpcIoPort* getChipPort() { return chipPort; }
	inline uint16_t getChipPortAddress() { return chipPortAddress; }
public:
	static bool isaBusMutexWait(int millisecondsTimeout);
	static bool isaBusMutexRelease();
	static bool isaBusMutexOpen();
	static bool isaBusMutexClose();
private:
	static const std::vector<LpcIoPort*> lpcIoPorts;

	void detectWinboundFintek(const LpcIoPort* port);
};

