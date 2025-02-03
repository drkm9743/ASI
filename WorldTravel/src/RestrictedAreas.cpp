#include "RestrictedAreas.h"
#include <fstream>  
#include <windows.h>
#include <string>
#include <ctime>
#include <iostream>
#include <vector>
#include "Settings.h"
#include "HelpText.h"


namespace restrictedAreas
{
	bool restrictedAreaClearance;
	bool cleanUpRequired = false;
	//Prison Bound Coords
	std::vector<float> PrisonLowerBox1Min = { 4006.0f, -3750.0f, 0.0f };
	std::vector<float> PrisonLowerBox1Max = { 4158.0f, -3694.0f, 7.0f };

	std::vector<float> PrisonLowerBox2Min = { 4051.0f, -3714.0f, 0.0f };
	std::vector<float> PrisonLowerBox2Max = { 4289.0f, -3606.0f, 7.0f };

	std::vector<float> PrisonLowerBox3Min = { 4051.0f, -3606.0f, 0.0f };
	std::vector<float> PrisonLowerBox3Max = { 4245.0f, -3580.0f, 7.0f };

	std::vector<float> PrisonUpperBox1Min = { 4004.0f, -3757.0f, 7.0f };
	std::vector<float> PrisonUpperBox1Max = { 4160.0f, -3692.0f, 25.0f };

	std::vector<float> PrisonUpperBox2Min = { 4044.0f, -3714.0f, 7.0f };
	std::vector<float> PrisonUpperBox2Max = { 4293.0f, -3604.0f, 25.0f };

	std::vector<float> PrisonUpperBox3Min = { 4044.0f, -3606.0f, 7.0f };
	std::vector<float> PrisonUpperBox3Max = { 4249.0f, -3577.0f, 25.0f };

	std::vector<float> PrisonAirspaceBox1Min = { 4004.0f, -3757.0f, 25.0f };
	std::vector<float> PrisonAirspaceBox1Max = { 4160.0f, -3692.0f, 100.0f };

	std::vector<float> PrisonAirspaceBox2Min = { 4044.0f, -3714.0f, 25.0f };
	std::vector<float> PrisonAirspaceBox2Max = { 4293.0f, -3604.0f, 100.0f };

	std::vector<float> PrisonAirspaceBox3Min = { 4044.0f, -3606.0f, 25.0f };
	std::vector<float> PrisonAirspaceBox3Max = { 4249.0f, -3577.0f, 100.0f };

	int prisonAlertLevel = 0;
	int prisonReactionTime = 1;
	int prisonGuardAnnouncerTime = 0;
	int prisonGuardAnnouncerTimeInterval = 15;
	int prisonAirspaceAlertLevel = 0;
	int prisonAirspaceReactionTime = 5;


	//UN HQ Bound Coords
	std::vector<float> UNHQBoxMin = { 5325.34f, -2952.33f, 14.15f };
	std::vector<float> UNHQBoxMax = { 5430.27f, -2727.15f, 51.45f };
	int uNHQAlertLevel = 0;
	int uNHQReactionTime = 1;

	bool isPlayerInRestrictedArea = false;
	Player playerPed;


	bool RestrictedAreaBreached(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
	{
		Entity player = playerPed;

		if (PED::IS_PED_IN_ANY_VEHICLE(player, false)) {
			player = PED::GET_VEHICLE_PED_IS_USING(player);
		}
		if (ENTITY::IS_ENTITY_IN_AREA(player, minX, minY, minZ, maxX, maxY, maxZ, false, true, false)
			|| GAMEPLAY::IS_PROJECTILE_IN_AREA(minX, minY, minZ, maxX, maxY, maxZ, true)
			|| GAMEPLAY::IS_BULLET_IN_BOX(minX, minY, minZ, maxX, maxY, maxZ, true))
		{
			return true;
		}
		return false;
	}

	bool PrisonBreach()
	{
		if (RestrictedAreaBreached(PrisonLowerBox1Min[0], PrisonLowerBox1Min[1], PrisonLowerBox1Min[2], PrisonLowerBox1Max[0], PrisonLowerBox1Max[1], PrisonLowerBox1Max[2]) ||
			RestrictedAreaBreached(PrisonLowerBox2Min[0], PrisonLowerBox2Min[1], PrisonLowerBox2Min[2], PrisonLowerBox2Max[0], PrisonLowerBox2Max[1], PrisonLowerBox2Max[2]) ||
			RestrictedAreaBreached(PrisonLowerBox3Min[0], PrisonLowerBox3Min[1], PrisonLowerBox3Min[2], PrisonLowerBox3Max[0], PrisonLowerBox3Max[1], PrisonLowerBox3Max[2]) ||
			RestrictedAreaBreached(PrisonUpperBox1Min[0], PrisonUpperBox1Min[1], PrisonUpperBox1Min[2], PrisonUpperBox1Max[0], PrisonUpperBox1Max[1], PrisonUpperBox1Max[2]) ||
			RestrictedAreaBreached(PrisonUpperBox2Min[0], PrisonUpperBox2Min[1], PrisonUpperBox2Min[2], PrisonUpperBox2Max[0], PrisonUpperBox2Max[1], PrisonUpperBox2Max[2]) ||
			RestrictedAreaBreached(PrisonUpperBox3Min[0], PrisonUpperBox3Min[1], PrisonUpperBox3Min[2], PrisonUpperBox3Max[0], PrisonUpperBox3Max[1], PrisonUpperBox3Max[2]))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool PrisonAirspaceBreach()
	{
		return (RestrictedAreaBreached(PrisonAirspaceBox1Min[0], PrisonAirspaceBox1Min[1], PrisonAirspaceBox1Min[2], PrisonAirspaceBox1Max[0], PrisonAirspaceBox1Max[1], PrisonAirspaceBox1Max[2]) ||
				RestrictedAreaBreached(PrisonAirspaceBox2Min[0], PrisonAirspaceBox2Min[1], PrisonAirspaceBox2Min[2], PrisonAirspaceBox2Max[0], PrisonAirspaceBox2Max[1], PrisonAirspaceBox2Max[2]) ||
				RestrictedAreaBreached(PrisonAirspaceBox3Min[0], PrisonAirspaceBox3Min[1], PrisonAirspaceBox3Min[2], PrisonAirspaceBox3Max[0], PrisonAirspaceBox3Max[1], PrisonAirspaceBox3Max[2]));
	}

	void Prison()
	{
		Vector3 playerPostion = ENTITY::GET_ENTITY_COORDS(playerPed, true);

		
		if (PrisonBreach())
		{
			if (prisonAlertLevel < prisonReactionTime)
			{
				prisonAlertLevel++;
			}
			if (prisonGuardAnnouncerTime < prisonGuardAnnouncerTimeInterval)
			{
				prisonGuardAnnouncerTime++;
			}
			else
			{
				prisonGuardAnnouncerTime = 0;
			}
			PLAYER::SET_PLAYER_WANTED_CENTRE_POSITION(PLAYER::PLAYER_ID(), playerPostion.x, playerPostion.y, playerPostion.z);
		}
		else if (PrisonAirspaceBreach())
		{
			if (prisonAirspaceAlertLevel == prisonAirspaceReactionTime)
			{
				prisonAlertLevel = 1;
			}
			if (prisonAirspaceAlertLevel < prisonAirspaceReactionTime)
			{
				prisonAirspaceAlertLevel++;
			}
		}
		else if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) == 0 && prisonAlertLevel > 0)
		{
			prisonAlertLevel = 0;
			prisonAirspaceAlertLevel = 0;
			prisonGuardAnnouncerTime = 0;
			if (AUDIO::IS_ALARM_PLAYING("ascf_alarms"))
			{
				AUDIO::STOP_ALARM("ascf_alarms", true);
			}
		}
		
		if (prisonAirspaceAlertLevel == 1)
		{
			if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed))
			{
			}
		}
		if (prisonAlertLevel == 1)
		{
			if (!AUDIO::IS_ALARM_PLAYING("ascf_alarms"))
			{
				if (AUDIO::PREPARE_ALARM("ascf_alarms"))
				{
					AUDIO::START_ALARM("ascf_alarms", false);
				}
			}

			if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4)
			{
				//worldtravel::HelpText::DisplayHelpText("Wanted level should be 4 stars.");
				PLAYER::SET_PLAYER_WANTED_LEVEL_NO_DROP(PLAYER::PLAYER_ID(), 4, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_PLAYER_WANTED_CENTRE_POSITION(PLAYER::PLAYER_ID(), playerPostion.x, playerPostion.y, playerPostion.z);
			}
			if (prisonGuardAnnouncerTime == 1)
			{
				//We'll need to spawn scripted peds to do it the way R* did.
				//AUDIO::PLAY_PED_AMBIENT_SPEECH_WITH_VOICE_NATIVE(playerPed, "PRISON_TANNOY_ALARM", "PRISON_ANNOUNCER", "SPEECH_PARAMS_FORCE_FRONTEND", true);
				AUDIO::PLAY_AMBIENT_SPEECH_FROM_POSITION_NATIVE("PRISON_TANNOY_ALARM", "PRISON_ANNOUNCER", 4205.2f, -3652.7f, 13.50f, "SPEECH_PARAMS_FORCE_FRONTEND");
			}
		}

		
	}

	bool UNHQBreach()
	{
		if (RestrictedAreaBreached(UNHQBoxMin[0], UNHQBoxMin[1], UNHQBoxMin[2], UNHQBoxMax[0], UNHQBoxMax[1], UNHQBoxMax[2]))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void UNHQ()
	{
		Vector3 playerPostion = ENTITY::GET_ENTITY_COORDS(playerPed, true);
		if (UNHQBreach())
		{
			uNHQAlertLevel = 1;
			PLAYER::SET_PLAYER_WANTED_CENTRE_POSITION(PLAYER::PLAYER_ID(), playerPostion.x, playerPostion.y, playerPostion.z);
		}
		else if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) == 0 && uNHQAlertLevel > 0)
		{
			uNHQAlertLevel = 0;
		}
		if (uNHQAlertLevel == 1)
		{
			if (PLAYER::GET_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID()) < 4)
			{
				//worldtravel::HelpText::DisplayHelpText("Wanted level should be 4 stars.");
				PLAYER::SET_PLAYER_WANTED_LEVEL_NO_DROP(PLAYER::PLAYER_ID(), 4, 0);
				PLAYER::SET_PLAYER_WANTED_LEVEL_NOW(PLAYER::PLAYER_ID(), 0);
				PLAYER::SET_PLAYER_WANTED_CENTRE_POSITION(PLAYER::PLAYER_ID(), playerPostion.x, playerPostion.y, playerPostion.z);
			}
		}
	}

	void RestrictedAreasMain()
	{
		Settings::Load();
		restrictedAreaClearance = Settings::GrantAccessToRestrictedAreas;
		if (!restrictedAreaClearance)
		{
			while (true)
			{
				playerPed = PLAYER::PLAYER_PED_ID();
				if (worldtravel::IsLibertyCity())
				{
					cleanUpRequired = true;
					WAIT(1000);
					Prison();
					UNHQ();
				}
				else if (cleanUpRequired)
				{
					prisonAirspaceAlertLevel = 0;
					prisonAlertLevel = 0;
					if (AUDIO::IS_ALARM_PLAYING("ascf_alarms"))
					{
						AUDIO::STOP_ALARM("ascf_alarms", true);
					}
					cleanUpRequired = false;
				}
				WAIT(0);
			}
		}
	}
}

void RestrictedAreas()
{
	srand(GetTickCount());
	restrictedAreas::RestrictedAreasMain();
}