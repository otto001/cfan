#pragma once
#include <string>
#include <vector>


class Device
{
public:
	Device(uint8_t type, uint16_t handle, std::vector<uint8_t>& data, std::vector<std::string>& stringData);

	virtual void init();

	virtual std::string report();
protected:
	std::string manufacturerName;
	std::string productName;
	std::string serialNumber;
	std::string version;
	std::vector<std::string> stringData;
	std::vector<uint8_t> data;
	uint8_t type;
	uint16_t handle;





	std::string getStringDataEntry(int offset) {
		if (offset < data.size() && data[offset] > 0 && data[offset] <= stringData.size()) {
			return stringData[data[offset] - 1];
		}
		else {
			return "";
		}
	}

};

