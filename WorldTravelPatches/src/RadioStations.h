#pragma once
#include <cstdint>
#include <string>
#include "Hooking.Patterns.h"
#include <MinHook.h>
#include "Hooking.h"

class RadioStations
{
public:
	static void Patch()
	{
		{
			uint8_t* maxRadioStations = hook::get_pattern<uint8_t>("8D 5E 60 89 35", 2);
			hook::put<uint8_t>(maxRadioStations, 127);
			uint32_t* radioStationsMemSize = (uint32_t*)(maxRadioStations + 0x26);
			hook::put<uint32_t>(radioStationsMemSize, 127 * 8);
		}

		{
			uint8_t* maxRadioStations = hook::get_pattern<uint8_t>("BD 60 00 00 00 E9", 1);
			hook::put<uint8_t>(maxRadioStations, 127);
			uint32_t* radioStationsMemSize = (uint32_t*)(maxRadioStations + 0x43);
			hook::put<uint32_t>(radioStationsMemSize, 127 * 8);
		}

		{
			uint8_t* maxRadioStations = hook::get_pattern<uint8_t>("45 8D 67 ? 8B C6", 3);
			hook::put<uint8_t>(maxRadioStations, 127);
			uint32_t* radioStationsMemSize = (uint32_t*)(maxRadioStations + 0x141);
			hook::put<uint32_t>(radioStationsMemSize, 127 * 8);
		}
	}
};