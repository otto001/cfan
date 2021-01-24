#include "../pch.h"
#include "SuperIo.h"
#include "NCT6775.h"

SuperIo::SuperIo(Chip _chip, uint8_t _revision, uint16_t _port, LpcIoPort* _lpcPort) : chip(_chip), revision(_revision), port(_port), lpcPort(_lpcPort)
{
}

SuperIo* SuperIo::constructChip(Chip _chip, uint8_t _revision, uint16_t _port, LpcIoPort* _lpcPort)
{
	switch (_chip) {
	case Chip::NCT6771F:
	case Chip::NCT6776F:
	case Chip::NCT610X:
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
		return new NCT6775(_chip, _revision, _port, _lpcPort);
	default:
		break;
	}
	return nullptr;
}
