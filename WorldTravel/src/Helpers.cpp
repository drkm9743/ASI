#include "Minimap.h"
#include <fstream>  
#include <windows.h>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "MpMap.h"

namespace helpers
{
	// Player Objects
	Ped playerPed;
	BOOL bPlayerExists;
	Vector3 PlayerPosition;

	// Interior Cords
	std::vector<float> heist_police_dlc = { 442.4296f, -985.067f, 29.88529f };
	std::vector<float> gr_grdlc_int_01 = { 1103.562f, -3000.0f, -40.0f };
	std::vector<float> xm_x17dlc_int_01 = { 520.0f, 4750.0f, -70.0f };
	std::vector<float> xm_x17dlc_int_sub = { 512.7686f, 4851.981f, -62.90245f };
	std::vector<float> ba_dlc_int_03_ba = { -1421.015f, -3012.587f, -80.0f };
	std::vector<float> h4_interior_0_int_sub = { 1560.0f, 400.0f, -50.0f };
	std::vector<float> dlc_int_01_xm3 = { 485.0f, -2625.0f, -50.0f };
	std::vector<float> dlc_int_01_m23_1 = { -880.0f, -2770.0f, -50.0f };
	bool tempWaterSwapActive = false;
	bool hasCayoLoadedExternally = false;

	// Streaming Data Reference

	std::vector<std::string> cayoInteriors = { "h4_islandx_mansion_vault",
												"h4_islandx_mansion_lockup_03",
												"h4_islandx_mansion_lockup_02",
												"h4_islandx_mansion_lockup_01",
												"h4_islandx_mansion_office",
												"h4_mph4_airstrip_interior_0_airstrip_hanger" };
	std::vector<std::string> cayoInstancePlacement = { "h4_mph4_terrain_01_grass_0",
														"h4_mph4_terrain_01_grass_1",
														"h4_mph4_terrain_02_grass_0",
														"h4_mph4_terrain_02_grass_1",
														"h4_mph4_terrain_02_grass_2",
														"h4_mph4_terrain_02_grass_3",
														"h4_mph4_terrain_04_grass_0",
														"h4_mph4_terrain_04_grass_1",
														"h4_mph4_terrain_05_grass_0",
														"h4_mph4_terrain_06_grass_0" };
	std::vector<std::string> cayoOccl = { "h4_mph4_terrain_occ_00",
											"h4_mph4_terrain_occ_01",
											"h4_mph4_terrain_occ_02",
											"h4_mph4_terrain_occ_03",
											"h4_mph4_terrain_occ_04",
											"h4_mph4_terrain_occ_05",
											"h4_mph4_terrain_occ_06",
											"h4_mph4_terrain_occ_07",
											"h4_mph4_terrain_occ_08",
											"h4_mph4_terrain_occ_09" };


	void initialize()
	{
		for (int i = 0; i < cayoInteriors.size(); i++)
		{
			STREAMING::REMOVE_IPL(const_cast<char*>(cayoInteriors[i].c_str()));
		}

		for (int i = 0; i < cayoInstancePlacement.size(); i++)
		{
			STREAMING::REMOVE_IPL(const_cast<char*>(cayoInstancePlacement[i].c_str()));
		}

		for (int i = 0; i < cayoOccl.size(); i++)
		{
			STREAMING::REMOVE_IPL(const_cast<char*>(cayoOccl[i].c_str()));
		}
	}

	// Fix for Cayo Perico Island Hopper not functioning correctly.
	void CayoPericoIslandHopperHelper()
	{
		if (!worldtravel::IsCayoPerico())
		{
			if (!hasCayoLoadedExternally && STREAMING::IS_IPL_ACTIVE("h4_islandairstrip_slod"))
			{
				for (int i = 0; i < cayoInteriors.size(); i++)
				{
					if (!STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoInteriors[i].c_str())))
					{
						STREAMING::REQUEST_IPL(const_cast<char*>(cayoInteriors[i].c_str()));
					}
				}
				for (int i = 0; i < cayoInstancePlacement.size(); i++)
				{
					if (!STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoInstancePlacement[i].c_str())))
					{
						STREAMING::REQUEST_IPL(const_cast<char*>(cayoInstancePlacement[i].c_str()));
					}
				}
				for (int i = 0; i < cayoOccl.size(); i++)
				{
					if (!STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoOccl[i].c_str())))
					{
						STREAMING::REQUEST_IPL(const_cast<char*>(cayoOccl[i].c_str()));
					}
				}
				hasCayoLoadedExternally = true;
			}
			else if (hasCayoLoadedExternally && !STREAMING::IS_IPL_ACTIVE("h4_islandairstrip_slod"))
			{
				for (int i = 0; i < cayoInteriors.size(); i++)
				{
					if (STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoInteriors[i].c_str())))
					{
						STREAMING::REMOVE_IPL(const_cast<char*>(cayoInteriors[i].c_str()));
					}
				}
				for (int i = 0; i < cayoInstancePlacement.size(); i++)
				{
					if (STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoInstancePlacement[i].c_str())))
					{
						STREAMING::REMOVE_IPL(const_cast<char*>(cayoInstancePlacement[i].c_str()));
					}
				}
				for (int i = 0; i < cayoOccl.size(); i++)
				{
					if (STREAMING::IS_IPL_ACTIVE(const_cast<char*>(cayoOccl[i].c_str())))
					{
						STREAMING::REMOVE_IPL(const_cast<char*>(cayoOccl[i].c_str()));
					}
				}
				hasCayoLoadedExternally = false;
			}
		}
	}

	// Fix for interiors being flooded
	void InteriorWaterFix()
	{
		//int playerInteriorId = INTERIOR::GET_INTERIOR_FROM_ENTITY(player);
		Vector3 cameraCoords;
		if (CAM::IS_GAMEPLAY_CAM_RENDERING())
			cameraCoords = CAM::GET_GAMEPLAY_CAM_COORD();
		else
			cameraCoords = CAM::GET_CAM_COORD(CAM::GET_RENDERING_CAM());
		float cameraCoordsX = cameraCoords.x;
		float cameraCoordsY = cameraCoords.y;
		float cameraCoordsZ = cameraCoords.z;
		int playerInteriorId = INTERIOR::GET_INTERIOR_AT_COORDS(cameraCoordsX, cameraCoordsY, cameraCoordsZ);

		if (!worldtravel::IsLosSantos())
		{
			if ((playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(gr_grdlc_int_01[0], gr_grdlc_int_01[1], gr_grdlc_int_01[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(xm_x17dlc_int_01[0], xm_x17dlc_int_01[1], xm_x17dlc_int_01[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(xm_x17dlc_int_sub[0], xm_x17dlc_int_sub[1], xm_x17dlc_int_sub[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(ba_dlc_int_03_ba[0], ba_dlc_int_03_ba[1], ba_dlc_int_03_ba[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(h4_interior_0_int_sub[0], h4_interior_0_int_sub[1], h4_interior_0_int_sub[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(dlc_int_01_xm3[0], dlc_int_01_xm3[1], dlc_int_01_xm3[2]) ||
				playerInteriorId == INTERIOR::GET_INTERIOR_AT_COORDS(dlc_int_01_m23_1[0], dlc_int_01_m23_1[1], dlc_int_01_m23_1[2])) &&
				playerInteriorId != 0 &&
				!tempWaterSwapActive)
			{
				STREAMING::LOAD_GLOBAL_WATER_FILE(0);
				PED::CLEAR_PED_WETNESS(playerPed);
				tempWaterSwapActive = true;
			}
			else if (tempWaterSwapActive && playerInteriorId == 0)
			{
				//WAIT(1000);
				if (worldtravel::IsCayoPerico())
					STREAMING::LOAD_GLOBAL_WATER_FILE(1);
				else if (worldtravel::IsLibertyCity())
					STREAMING::LOAD_GLOBAL_WATER_FILE(2);
				tempWaterSwapActive = false;
				if (NETWORK::NETWORK_IS_IN_SESSION())
				{
					NETWORK::NETWORK_SET_PROPERTY_ID(100);
				}
			}
		}
	}

	// Blocks NPCs from spawning in unloaded areas
	void NpcSpawnBlocker()
	{
		//block traffic and peds around Los Santos if it is not loaded
		if (!STREAMING::IS_IPL_ACTIVE("cs5_lod"))
		{
			if (!ENTITY::IS_ENTITY_IN_AREA(playerPed, 2600.0f, -6600.0f, -10000.0f, 8300.0f, -2500.0f, 10000.0f, false, false, false) &&
				!ENTITY::IS_ENTITY_IN_AREA(playerPed, 3000.0f, -2500.0f, -10000.0f, 8300.0f, -1700.0f, 10000.0f, false, false, false) &&
				!ENTITY::IS_ENTITY_IN_AREA(playerPed, 3400.0f, -1700.0f, -10000.0f, 8300.0f, -900.0f, 10000.0f, false, false, false))
			{
				//worldtravel::HelpText::DisplayHelpText("NPCs blocked in this area when Los Santos is disabled.");
				VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);
			}
		}

		//block traffic and peds around North Yankton/Cayo Perico if they're both not loaded
		if (!STREAMING::IS_IPL_ACTIVE("prologuerd") && !STREAMING::IS_IPL_ACTIVE("h4_islandx"))
		{
			if (ENTITY::IS_ENTITY_IN_AREA(playerPed, 2200.0f, -5600.0f, -10000.0f, 4100.0f, -4000.0f, 10000.0f, false, false, false) ||
				ENTITY::IS_ENTITY_IN_AREA(playerPed, 4100.0f, -5600.0f, -10000.0f, 6500.0f, -4600.0f, 10000.0f, false, false, false))
			{
				//worldtravel::HelpText::DisplayHelpText("NPCs blocked in this area when North Yankton and Cayo Perico are disabled.");
				VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);
			}
		}

		//block traffic and peds around Liberty City if it's not loaded
		if (!STREAMING::IS_IPL_ACTIVE("manhat06_slod"))
		{
			if (ENTITY::IS_ENTITY_IN_AREA(playerPed, 2600.0f, -4200.0f, -10000.0f, 8300.0f, -2500.0f, 10000.0f, false, false, false) ||
				ENTITY::IS_ENTITY_IN_AREA(playerPed, 3000.0f, -2500.0f, -10000.0f, 8300.0f, -1700.0f, 10000.0f, false, false, false) ||
				ENTITY::IS_ENTITY_IN_AREA(playerPed, 3400.0f, -1700.0f, -10000.0f, 8300.0f, -900.0f, 10000.0f, false, false, false))
			{
				//worldtravel::HelpText::DisplayHelpText("NPCs blocked in this area when Liberty City is disabled.");
				VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				VEHICLE::SET_PARKED_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
				PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);
			}
		}
	}

	void HelpersMain()
	{
		initialize();
		while (true)
		{
			playerPed = PLAYER::PLAYER_ID();
			playerPed = PLAYER::PLAYER_PED_ID();
			bPlayerExists = ENTITY::DOES_ENTITY_EXIST(playerPed);
			CayoPericoIslandHopperHelper();
			worldtravel::MpMap::CheckIfMPMapIsActive();
			InteriorWaterFix();
			NpcSpawnBlocker();
			WAIT(0);
		}
	}
}

void Helpers()
{
	srand(GetTickCount());
	helpers::HelpersMain();
}
