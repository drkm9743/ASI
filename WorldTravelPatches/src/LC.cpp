#include "Water.h"
#include "Globals.h"
#include "Paths.h"

#define export extern "C" __declspec(dllexport)

export void Water_Load(const char* filePath)
{
	Water::Load(filePath);
}

export void Water_BeginLoadScreen()
{
	Water::BeginLoadScreen();
}

export void Water_EndLoadScreen()
{
	Water::EndLoadScreen();
}

export void Paths_Switch()
{
	Paths::SwitchPaths();
}

// backwards compatibility
export void LoadWaterData(const char* filePath) { Water_Load(filePath); }
export void BeginLoadScreen() { Water_BeginLoadScreen(); }
export void EndLoadScreen() { Water_EndLoadScreen(); }

export unsigned int Globals_GetMapId()
{
	return globals::MapId;
}

export void Globals_SetMapId(unsigned int mapId)
{
	globals::MapId = mapId;
}