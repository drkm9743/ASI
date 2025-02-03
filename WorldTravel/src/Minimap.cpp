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

	static void CreateMinimap()
	{
		if (worldtravel::IsLibertyCity())
		{
			/*if (INTERIOR::GET_INTERIOR_FROM_ENTITY(PLAYER::PLAYER_PED_ID()) == INTERIOR::GET_INTERIOR_AT_COORDS(4797.335f, -2851.378f, 5.098513f)) // e2_gayclub
			{
				return;
			}*/

			UI::SET_RADAR_AS_EXTERIOR_THIS_FRAME();
			UI::SET_RADAR_AS_INTERIOR_THIS_FRAME(GAMEPLAY::GET_HASH_KEY("v_fakelibertycity"), LibertyCityGFXPos[0], LibertyCityGFXPos[1], 0, 0);
		}

	}

	static void MinimapMain()
	{
		while (true)
		{
			CreateMinimap();
			WAIT(0);
		}
	}
}

// Hooks to disable rendering of the los santos minimap

static void (*gImpl_CMiniMap_RenderThread__RenderBitmaps)();
static void lcImpl_CMiniMap_RenderThread__RenderBitmaps()
{
	if (!worldtravel::IsLibertyCity())
		gImpl_CMiniMap_RenderThread__RenderBitmaps();
}

static void (*gImpl_CSupertiles__Render)(void* self);
static void lcImpl_CSupertiles__Render(void* self)
{
	if (!worldtravel::IsLibertyCity())
		gImpl_CSupertiles__Render(self);
}

void Minimap_Hooks()
{
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

void Minimap()
{
	srand(GetTickCount());
	minimap::MinimapMain();
}
