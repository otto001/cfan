#include "../pch.h"
#include "MainBoard.h"
#include <string>
#include <sstream>

MainBoard::MainBoard(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData) : Device(type, handle, data, stringData) {
}


void MainBoard::init()
{
	lpcIo = new LpcIo();
	lpcIo->init();
	lpcIo->detect();

	superIo = SuperIo::constructChip(lpcIo->getChip(), lpcIo->getChipRevision(), lpcIo->getChipPortAddress(), lpcIo->getChipPort());
}

std::string MainBoard::report()
{
	std::ostringstream result;
	superIo->update();
	result << this->manufacturerName << std::endl;
	result << superIo->getFans()[2] << std::endl;

	return result.str();
}
