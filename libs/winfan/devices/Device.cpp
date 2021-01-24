#include "../pch.h"
#include "Device.h"
#include <string>
#include <sstream>

Device::Device(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData) {
	this->type = type;
	this->handle = handle;
	this->stringData = stringData;
	this->data = data;

	this->manufacturerName = getStringDataEntry(4);
}

void Device::init()
{

}

std::string Device::report()
{
	std::ostringstream result;
	result << this->manufacturerName << std::endl;

	return result.str();
}
