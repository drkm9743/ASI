#include "Minimap.h"
#include <fstream>  
#include <windows.h>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "Hooking.h"
#include "Hooking.Patterns.h"
#include <MinHook.h>

namespace minimap
{
	// Radar Coords
	std::vector<float> LibertyCityGFXPos = { 5490.0f, -2697.0f, 0.0f };

	bool IsPlayerInsideInterior()
	{
		Ped PlayerPed = PLAYER::PLAYER_PED_ID();
		int InteriorID = INTERIOR::GET_INTERIOR_FROM_ENTITY(PlayerPed);

		if (InteriorID != 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	static void CreateMinimap()
	{
		if (worldtravel::IsLibertyCity())
		{
			UI::SET_MINIMAP_COMPONENT(14, true, -1);
		}

	}

	static void MinimapMain()
	{
		while (true)
		{
			//CreateMinimap();
			WAIT(0);
		}
	}
}

// Hooks to disable rendering of the los santos minimap

static void (*gImpl_CMiniMap_RenderThread__RenderBitmaps)();
static void lcImpl_CMiniMap_RenderThread__RenderBitmaps()
{
	if (worldtravel::gameversion::GetGameVersion())
	{

	}
	else
	{
		if (worldtravel::IsLosSantos() || worldtravel::IsNorthYankton() || worldtravel::IsCayoPerico())
			gImpl_CMiniMap_RenderThread__RenderBitmaps();
	}
}

static void (*gImpl_CSupertiles__Render)(void* self);
static void lcImpl_CSupertiles__Render(void* self)
{
	if (worldtravel::gameversion::GetGameVersion())
	{

	}
	else
	{
		if (worldtravel::IsLosSantos() || worldtravel::IsNorthYankton() || worldtravel::IsCayoPerico())
			gImpl_CSupertiles__Render(self);
	}
}

void Minimap_Hooks()
{
	if (worldtravel::gameversion::GetGameVersion())
	{

	}
	else
	{
		InitMinimapComponentControl();
		RegisterMinimapNatives();

		{
			auto location = hook::get_pattern("48 8B C4 55 53 56 57 41 56 41 57 48 8D 68 ? 48 81 EC B8 00 00 00");
			MH_CreateHook(location, lcImpl_CMiniMap_RenderThread__RenderBitmaps, (void**)&gImpl_CMiniMap_RenderThread__RenderBitmaps);
			MH_EnableHook(location);
		}

		{
			auto location = hook::get_pattern("48 8B C4 48 89 58 ? 48 89 68 ? 48 89 70 ? 48 89 78 ? 41 56 48 83 EC 20 4C 8B F1 33 DB");
			MH_CreateHook(location, lcImpl_CSupertiles__Render, (void**)&gImpl_CSupertiles__Render);
			MH_EnableHook(location);
		}
	}
}


void Minimap()
{
	srand(GetTickCount());
	minimap::MinimapMain();
}
