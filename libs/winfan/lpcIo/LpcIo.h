#pragma once

#include <synchapi.h>
#include <vector>
#include "LpcIoPort.h"

class SuperIo;

class LpcIo
{
public:
	void init();
    [[nodiscard]] SuperIo* detect();

private:
	Chip chip;
	LDN ldn;
	uint8_t chipId;
	uint8_t chipRevision;

public:
	inline Chip getChip() { return chip; }
	inline uint8_t getChipId() { return chipId; }
	inline uint8_t getChipRevision() { return chipRevision; }
	//inline LpcIoPort* getChipPort() { return chipPort; }
	//inline uint16_t getChipPortAddress() { return chipPortAddress; }

private:
	static const std::vector<LpcIoPort*> lpcIoPorts;

    SuperIo* detectWinboundFintek(const LpcIoPort* port);
};

