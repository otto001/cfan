#include "../pch.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>

#include "../superIo/SmBios.h"

void SmBios::init()
{
    RawSMBIOSData* smBiosData = NULL;
    this->getRaw(&smBiosData);
    this->parseRaw(smBiosData);
    for (auto device : devices) {
        device->init();
    }
}

bool SmBios::getRaw(RawSMBIOSData** data) {
    uint64_t error = ERROR_SUCCESS;
    uint32_t smBiosDataSize = 0;
    RawSMBIOSData* smBiosData = NULL; // Defined in this link
    uint64_t bytesWritten = 0;

    // Query size of SMBIOS data.
    smBiosDataSize = GetSystemFirmwareTable('RSMB', 0, NULL, 0);

    // Allocate memory for SMBIOS data
    smBiosData = (RawSMBIOSData*)HeapAlloc(GetProcessHeap(), 0, smBiosDataSize);
    if (!smBiosData) {
        error = ERROR_OUTOFMEMORY;
        return false;
    }


    // Retrieve the SMBIOS table
    bytesWritten = GetSystemFirmwareTable('RSMB', 0, smBiosData, smBiosDataSize);

    if (bytesWritten != smBiosDataSize) {
        error = ERROR_INVALID_DATA;
        return false;
    }



    *data = smBiosData;
    return true;
}

void SmBios::parseRaw(RawSMBIOSData* data)
{
    size_t offset = 0;
    uint8_t type = data->raw[offset];
    uint8_t* raw = data->raw;
    size_t rawLength = data->length;

    while (offset + 4 < rawLength && type != 127) {

        type = raw[offset];
        size_t length = raw[offset + 1];
        uint16_t handle = (uint16_t)((raw[offset + 2] << 8) | raw[offset + 3]);

        if (offset + length > rawLength) {
            break;
        }

        // copy entry data
        std::vector<uint8_t> data;
        data.assign(raw + offset, raw + offset + length);


        offset += length;

        if (offset < rawLength && raw[offset] == 0) {
            offset++;

        }
        std::vector<std::string> strings;


        while (offset < rawLength && raw[offset] != 0) {
            std::string string;

            while (offset < rawLength && raw[offset] != 0) {
                string.push_back((char)raw[offset]);
                offset++;
            }

            offset++;
            strings.push_back(string);
        }
        offset++;

        Device* device;

        switch (type) {


        case 0x02: 
            mainBoard = new MainBoard(type, handle, data, strings);
            device = mainBoard;
            break;

        case 0x00:
            //BIOS INFO
        case 0x01:
            //SYSTEM INFO
        case 0x04:
            // PROCESSOR INFO
        case 0x11: 
            //MEMORY DEVICE INFO
        default: 
            device = new Device(type, handle, data, strings);
            break;
        }

        this->devices.push_back(device);

    }
}

std::string SmBios::report() {

    std::string result;
    for (auto device : devices) {
        result += device->report() + "\n\n";
    }
    return result;
}



