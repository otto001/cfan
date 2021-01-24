#pragma once
#include "Device.h"
#include "../lpcIo/LpcIo.h"
#include "../SuperIo/SuperIo.h"


class MainBoard : public Device
{
public:
	MainBoard(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData);

	void init() override;
	std::string report() override;

protected:
	LpcIo* lpcIo = NULL;
	SuperIo* superIo;
public:
    SuperIo *getSuperIo() const;

};

