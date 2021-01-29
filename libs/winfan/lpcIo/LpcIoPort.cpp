#include "../pch.h"
#include "LpcIoPort.h"
#include "../OlsDll.h"

void LpcIoPort::detectWinboundFintekEnter() const {
	OlsDll::writeIoPortByte(registerPort, 0x87);
	OlsDll::writeIoPortByte(registerPort, 0x87);
}

void LpcIoPort::detectWinboundFintekExit() const
{
	OlsDll::writeIoPortByte(registerPort, 0xAA);
}

void LpcIoPort::nuvotonDisableIOSpaceLock() const {
	const uint8_t NUVOTON_HARDWARE_MONITOR_IO_SPACE_LOCK = 0x28;

	uint8_t options = readRegister(NUVOTON_HARDWARE_MONITOR_IO_SPACE_LOCK);

	// if the i/o space lock is enabled
	if ((options & 0x10) > 0) {

		// disable the i/o space lock
		writeRegister(NUVOTON_HARDWARE_MONITOR_IO_SPACE_LOCK,
			(uint8_t)(options & ~0x10));
	}
}

void LpcIoPort::writeRegister(uint8_t reg, uint8_t value) const {
	OlsDll::writeIoPortByte(registerPort, reg);
	OlsDll::writeIoPortByte(valuePort, value);
}


uint8_t LpcIoPort::readRegister(uint8_t reg) const {
	uint8_t res;
	bool success = OlsDll::writeIoPortByte(registerPort, reg);
	if (success) {
		success = OlsDll::readIoPortByte(valuePort, &res);
		if (success) {
			return res;
		}
	}
	return 0;
}

uint16_t LpcIoPort::readRegisterWord(uint8_t reg) const {
	return (uint16_t)((readRegister(reg) << 8) | readRegister((byte)(reg + 1)));
}


void LpcIoPort::selectLdn(LDN ldn) const {
	OlsDll::writeIoPortByte(registerPort, DEVCIE_SELECT_REGISTER);
	OlsDll::writeIoPortByte(valuePort, (uint8_t) ldn);
}
