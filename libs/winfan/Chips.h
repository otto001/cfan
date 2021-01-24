#pragma once

enum class Chip {
	Unknown,
    NCT6771F = 0xB470,
    NCT6776F = 0xC330,
    NCT610X = 0xC452,
    NCT6779D = 0xC560,
    NCT6791D = 0xC803,
    NCT6792D = 0xC911,
    NCT6792DA = 0xC913,
    NCT6793D = 0xD121,
    NCT6795D = 0xD352,
    NCT6796D = 0xD423,
    NCT6796DR = 0xD42A,
    NCT6797D = 0xD451,
    NCT6798D = 0xD42B,
};

enum class LDN : uint8_t {
	Unknown,
	WINBOND_NUVOTON_HARDWARE_MONITOR_LDN = 0x0B
};