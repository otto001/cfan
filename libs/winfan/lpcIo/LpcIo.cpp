#include "../pch.h"
#include "LpcIo.h"
#include "../defines.h"
#include <iostream>
#include "../OlsDll.h"
#include "../Chips.h"
#include "../devices/mainboard/superIo/SuperIo.h"
#include "../devices/mainboard/superIo/NCT6775.h"
#include <chrono>
#include <thread>


const std::vector<LpcIoPort*> LpcIo::lpcIoPorts = {new LpcIoPort(0x2E, 0x2F), new LpcIoPort(0x4E, 0x4F)};

void LpcIo::init()
{
	
}

SuperIo* LpcIo::detect()
{
    chip = Chip::Unknown;
    ldn = LDN::Unknown;
    if (OlsDll::isaBusMutexWait(100)) {
        for (auto port : lpcIoPorts) {
            auto result = detectWinboundFintek(port);
            if (result) {
                OlsDll::isaBusMutexRelease();
                return result;
            }
        }
        OlsDll::isaBusMutexRelease();
    }
    return nullptr;
}

SuperIo* LpcIo::detectWinboundFintek(const LpcIoPort* port)
{
    port->detectWinboundFintekEnter();

    chipId = port->readRegister(CHIP_ID_REGISTER);
    chipRevision = port->readRegister(CHIP_REVISION_REGISTER);

    switch (chipId) {
        case 0xC8: {
            switch (chipRevision) {
                case 0x03:
                    chip = Chip::NCT6791D;
                    ldn = LDN::WINBOND_NUVOTON_HARDWARE_MONITOR_LDN;
                default:
                    break;
            }
        }
        case 0xD4: {
            switch (chipRevision) {
                case 0x2b:
                    chip = Chip::NCT6798D;
                    ldn = LDN::WINBOND_NUVOTON_HARDWARE_MONITOR_LDN;
                default:
                    break;
            }
        }

        default:
            break;
    }

    if (chip == Chip::Unknown) {
        std::cout << "Unknown Chip" << std::endl;
        if (chipId != 0 && chipId != 0xff) {
            port->detectWinboundFintekExit();
        }
        return nullptr;
    }
    port->selectLdn(ldn);
    uint16_t address = port->readRegisterWord(BASE_ADDRESS_REGISTER);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    uint16_t addressVerify = port->readRegisterWord(BASE_ADDRESS_REGISTER);


    uint16_t vendorID = port->readRegisterWord(FINTEK_VENDOR_ID_REGISTER);



    // disable the hardware monitor i/o space lock on NCT679XD chips
    if (address == addressVerify && (
            chip == Chip::NCT6791D ||
            chip == Chip::NCT6792D ||
            chip == Chip::NCT6792DA ||
            chip == Chip::NCT6793D ||
            chip == Chip::NCT6795D ||
            chip == Chip::NCT6796D ||
            chip == Chip::NCT6796DR ||
            chip == Chip::NCT6797D ||
            chip == Chip::NCT6798D))
    {
        port->nuvotonDisableIOSpaceLock();
    }

    port->detectWinboundFintekExit();

    if (address != addressVerify) {
        std::cerr << "Error: Address verification failed" << std::endl;
        return nullptr;
    }

    // some Fintek chips have address register offset 0x05 added already
    if ((address & 0x07) == 0x05)
        address &= 0xFFF8;

    if (address < 0x100 || (address & 0xF007) != 0) {
        std::cerr << "Error: Invalid address" << std::endl;
        return nullptr;
    }

    SuperIo* result = nullptr;

    switch (chip) {
//        case Chip::W83627DHG:
//        case Chip::W83627DHGP:
//        case Chip::W83627EHF:
//        case Chip::W83627HF:
//        case Chip::W83627THF:
//        case Chip::W83667HG:
//        case Chip::W83667HGB:
//        case Chip::W83687THF:
//            superIOs.Add(new W836XX(chip, revision, address));
//            break;
        case Chip::NCT610X:
        case Chip::NCT6771F:
        case Chip::NCT6776F:
        case Chip::NCT6779D:
        case Chip::NCT6791D:
        case Chip::NCT6792D:
        case Chip::NCT6792DA:
        case Chip::NCT6793D:
        case Chip::NCT6795D:
        case Chip::NCT6796D:
        case Chip::NCT6796DR:
        case Chip::NCT6797D:
        case Chip::NCT6798D:
            result = new NCT6775(chip, chipRevision, address, port);
            break;
//        case Chip::F71858:
//        case Chip::F71862:
//        case Chip::F71869:
//        case Chip::F71878AD:
//        case Chip::F71869A:
//        case Chip::F71882:
//        case Chip::F71889AD:
//        case Chip::F71889ED:
//        case Chip::F71889F:
//        case Chip::F71808E:
//            if (vendorID != FINTEK_VENDOR_ID) {
//                report.Append("Chip ID: 0x");
//                report.AppendLine(chip.ToString("X"));
//                report.Append("Chip revision: 0x");
//                report.AppendLine(revision.ToString("X",
//                                                    CultureInfo.InvariantCulture));
//                report.Append("Error: Invalid vendor ID 0x");
//                report.AppendLine(vendorID.ToString("X",
//                                                    CultureInfo.InvariantCulture));
//                report.AppendLine();
//                return false;
//            }
//            superIOs.Add(new F718XX(chip, address));
//            break;
        default: break;
    }
    
    
    std::cout << "SuperIO Chip Detected" << std::endl;
    return result;
}








