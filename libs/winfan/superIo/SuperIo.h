#ifndef WINFAN_SUPERIO_H
#define WINFAN_SUPERIO_H

#include <vector>
#include "../lpcIo/LpcIoPort.h"
#include "../Chips.h"


class SuperIo {
public:
    SuperIo(Chip chip, uint8_t revision, uint16_t port, LpcIoPort* lpcPort);
protected:
    uint16_t port;
    uint8_t revision;

    Chip chip;
    LpcIoPort* lpcPort;


    std::vector<float> voltages;
    std::vector<float> temperatures;
    std::vector<float> fans;
    std::vector<float> controls;

public:

    virtual void setControl(int index, uint8_t* value) {

    }
    virtual void update() {

    }

    inline const std::vector<float>& getVoltages() {
        return voltages;
    }

    inline const std::vector<float>& getTemperatures() {
        return temperatures;
    }

    inline const std::vector<float>& getFans() {
        return fans;
    }

    inline const std::vector<float>& getControls() {
        return controls;
    }

    static SuperIo* constructChip(Chip _chip, uint8_t _revision, uint16_t _port, LpcIoPort* _lpcPort);
};

#endif
