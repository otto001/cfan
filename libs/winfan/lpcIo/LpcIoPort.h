#pragma once
#include <cstdint>
#include "../Chips.h"

#define CHIP_ID_REGISTER 0x20
#define CHIP_REVISION_REGISTER 0x21
#define BASE_ADDRESS_REGISTER 0x60
#define BASE_ADDRESS_REGISTER 0x60
#define DEVCIE_SELECT_REGISTER 0x07
#define CONFIGURATION_CONTROL_REGISTER 0x02
#define FINTEK_VENDOR_ID_REGISTER 0x23


class LpcIoPort
{
	uint16_t registerPort;
	uint16_t valuePort;
public:

	LpcIoPort(uint16_t registerPortRegIn, uint16_t valuePortIn) {
		registerPort = registerPortRegIn;
		valuePort = valuePortIn;
	}

	void detectWinboundFintekEnter() const;
	void detectWinboundFintekExit() const;
	void nuvotonDisableIOSpaceLock() const;

	uint8_t readRegister(uint8_t reg) const;
	uint16_t readRegisterWord(uint8_t reg) const;

	void writeRegister(uint8_t reg, uint8_t value) const;


	void selectLdn(LDN ldn) const;


};

