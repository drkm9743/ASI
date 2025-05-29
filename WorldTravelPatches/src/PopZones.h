#pragma once
#include <cstdint>
#include <string>
#include <MinHook.h>
#include "Hooking.h"

class PopZones
{
public:
	static void Patch()
	{
		{
			uint8_t* location = hook::get_pattern<uint8_t>("E8 ? ? ? ? 0F BE 40 06 EB 09 E8 ? ? ? ? 0F BE 40 05"); // zone_commands::CommandGetZonePopSchedule
			hook::put<uint8_t>(location + 6, 182);
			hook::put<uint8_t>(location + 17, 182);

		}
		{
			uint8_t* location = hook::get_pattern<uint8_t>("0F BE 54 88 ? EB 5F 41 B8 ? ? ? ? E8"); // CPopCycle::UpdateCurrZoneFromCoors
			hook::put<uint8_t>(location + 1, 182);
		}
		{
			uint8_t* location = hook::get_pattern<uint8_t>("0F BE 54 88 ? EB 02 8B D3 89 15"); // CPopCycle::UpdateCurrZoneFromCoors
			hook::put<uint8_t>(location + 1, 182);
		}
	}
};