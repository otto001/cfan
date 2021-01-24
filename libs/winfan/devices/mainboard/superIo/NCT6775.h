#pragma once

#include "SuperIo.h"


enum class SourceNCT6771F : uint8_t {
    SYSTIN = 1,
    CPUTIN = 2,
    AUXTIN = 3,
    SMBUSMASTER = 4,
    PECI_0 = 5,
    PECI_1 = 6,
    PECI_2 = 7,
    PECI_3 = 8,
    PECI_4 = 9,
    PECI_5 = 10,
    PECI_6 = 11,
    PECI_7 = 12,
    PCH_CHIP_CPU_MAX_TEMP = 13,
    PCH_CHIP_TEMP = 14,
    PCH_CPU_TEMP = 15,
    PCH_MCH_TEMP = 16,
    PCH_DIM0_TEMP = 17,
    PCH_DIM1_TEMP = 18,
    PCH_DIM2_TEMP = 19,
    PCH_DIM3_TEMP = 20
};

enum class SourceNCT6776F : uint8_t {
    SYSTIN = 1,
    CPUTIN = 2,
    AUXTIN = 3,
    SMBUSMASTER_0 = 4,
    SMBUSMASTER_1 = 5,
    SMBUSMASTER_2 = 6,
    SMBUSMASTER_3 = 7,
    SMBUSMASTER_4 = 8,
    SMBUSMASTER_5 = 9,
    SMBUSMASTER_6 = 10,
    SMBUSMASTER_7 = 11,
    PECI_0 = 12,
    PECI_1 = 13,
    PCH_CHIP_CPU_MAX_TEMP = 14,
    PCH_CHIP_TEMP = 15,
    PCH_CPU_TEMP = 16,
    PCH_MCH_TEMP = 17,
    PCH_DIM0_TEMP = 18,
    PCH_DIM1_TEMP = 19,
    PCH_DIM2_TEMP = 20,
    PCH_DIM3_TEMP = 21,
    uint8_t_TEMP = 22
};

enum class SourceNCT67XXD : uint8_t {
    SYSTIN = 1,
    CPUTIN = 2,
    AUXTIN0 = 3,
    AUXTIN1 = 4,
    AUXTIN2 = 5,
    AUXTIN3 = 6,
    SMBUSMASTER_0 = 8,
    SMBUSMASTER_1 = 9,
    SMBUSMASTER_2 = 10,
    SMBUSMASTER_3 = 11,
    SMBUSMASTER_4 = 12,
    SMBUSMASTER_5 = 13,
    SMBUSMASTER_6 = 14,
    SMBUSMASTER_7 = 15,
    PECI_0 = 16,
    PECI_1 = 17,
    PCH_CHIP_CPU_MAX_TEMP = 18,
    PCH_CHIP_TEMP = 19,
    PCH_CPU_TEMP = 20,
    PCH_MCH_TEMP = 21,
    PCH_DIM0_TEMP = 22,
    PCH_DIM1_TEMP = 23,
    PCH_DIM2_TEMP = 24,
    PCH_DIM3_TEMP = 25,
    uint8_t_TEMP = 26
};

enum class SourceNCT610X : uint8_t {
    SYSTIN = 1,
    CPUTIN = 2,
    AUXTIN = 3,
    SMBUSMASTER_0 = 4,
    SMBUSMASTER_1 = 5,
    SMBUSMASTER_2 = 6,
    SMBUSMASTER_3 = 7,
    SMBUSMASTER_4 = 8,
    SMBUSMASTER_5 = 9,
    SMBUSMASTER_6 = 10,
    SMBUSMASTER_7 = 11,
    PECI_0 = 12,
    PECI_1 = 13,
    PCH_CHIP_CPU_MAX_TEMP = 14,
    PCH_CHIP_TEMP = 15,
    PCH_CPU_TEMP = 16,
    PCH_MCH_TEMP = 17,
    PCH_DIM0_TEMP = 18,
    PCH_DIM1_TEMP = 19,
    PCH_DIM2_TEMP = 20,
    PCH_DIM3_TEMP = 21,
    uint8_t_TEMP = 22
};


class NCT6775 : public SuperIo
{
public:
    NCT6775(Chip chip, uint8_t revision, uint16_t port, const LpcIoPort* lpcPort);
private:

    bool isNuvotonVendor;

    // Hardware Monitor
    const uint32_t ADDRESS_REGISTER_OFFSET = 0x05;
    const uint32_t DATA_REGISTER_OFFSET = 0x06;
    const uint8_t BANK_SELECT_REGISTER = 0x4E;

    // Consts 
    const uint16_t NUVOTON_VENDOR_ID = 0x5CA3;

    // Hardware Monitor Registers    
    uint16_t VENDOR_ID_HIGH_REGISTER;
    uint16_t VENDOR_ID_LOW_REGISTER;


    std::vector<uint16_t> FAN_PWM_OUT_REG;
    std::vector<uint16_t> FAN_PWM_COMMAND_REG;
    std::vector<uint16_t> FAN_CONTROL_MODE_REG;

    std::vector<uint16_t> fanRpmBaseRegister;
    int minFanRPM;

    std::vector<uint16_t> fanCountRegister;
    int maxFanCount;
    int minFanCount;

    std::vector<bool> restoreDefaultFanControlRequired;
    std::vector<uint8_t> initialFanControlMode;
    std::vector<uint8_t> initialFanPwmCommand;

    std::vector<uint16_t> voltageRegisters;
    uint16_t voltageVBatRegister;
    uint16_t vBatMonitorControlRegister;

    std::vector<uint8_t> temperaturesSource;

    std::vector<uint16_t> temperatureRegister;
    std::vector<uint16_t> temperatureHalfRegister;
    std::vector<int> temperatureHalfBit;
    std::vector<uint16_t> temperatureSourceRegister;

    std::vector<uint16_t*> alternateTemperatureRegister;


    uint8_t readByte(uint16_t address);
    void writeByte(uint16_t address, uint8_t value);

    bool getIsNuvotonVendor();
    void saveDefaultFanControl(int index);
    void restoreDefaultFanControl(int index);
    void disableIOSpaceLock();
public:
    void setFanControlMode(int index, uint8_t value) override;
    void setFanSpeed(int index, uint8_t value) override;
    void update() override;
    

};








