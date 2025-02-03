#include "PayNSpray.h"

namespace worldtravel
{
	namespace PayNSpray
	{
		std::string GereratePlate()
		{
			const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"; // Capital letters and digits
			const int length = 8;
			std::string result;

			// Seed the random number generator
			std::srand(static_cast<unsigned int>(std::time(0)));

			for (int i = 0; i < length; ++i) {
				// Generate a random index to pick a character from the charset
				int randomIndex = std::rand() % (sizeof(charset) - 1);
				result += charset[randomIndex];
			}

			return result;
		}
		void ResprayVehicle(Vehicle playerVehicle, std::string doorName)
		{
			ENTITY::FREEZE_ENTITY_POSITION(playerVehicle, true);
			CAM::DO_SCREEN_FADE_OUT(800);
			WAIT(800);
			OBJECT::DOOR_SYSTEM_SET_OPEN_RATIO(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 1.0f, false, false);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 6, false, false);
			while (!OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(6))
			{
				WAIT(0);
			}
			if (!NETWORK::NETWORK_IS_IN_SESSION())
			{
				TIME::ADD_TO_CLOCK_TIME(4, 0, 0);
				AUDIO::SKIP_RADIO_FORWARD();
			}
			VEHICLE::SET_VEHICLE_COLOUR_COMBINATION(playerVehicle, VEHICLE::GET_VEHICLE_COLOUR_COMBINATION(playerVehicle));
			VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(playerVehicle, (char*)GereratePlate().c_str());
			PLAYER::CLEAR_PLAYER_WANTED_LEVEL(PLAYER::PLAYER_ID());
			OBJECT::DOOR_SYSTEM_SET_OPEN_RATIO(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 0.0f, false, false);
			OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 0, false, false);
			while (!OBJECT::DOOR_SYSTEM_GET_DOOR_STATE(0))
			{
				WAIT(0);
			}
			ENTITY::FREEZE_ENTITY_POSITION(playerVehicle, false);
			CAM::DO_SCREEN_FADE_IN(800);
		}
		// void PayNSpray(std::string doorName, Vector3 garageBoundsMin, Vector3 garageBoundsMax)
		void PayNSpray(std::string doorName, std::string garage)
		{
			Player playerPed = PLAYER::PLAYER_PED_ID();
			Vehicle playerVehicle;
			Entity player = playerPed;
			
			if (PED::IS_PED_IN_ANY_VEHICLE(player, 0))
			{
				playerVehicle = PED::GET_VEHICLE_PED_IS_USING(player);
				Vector3 playerVelocity = ENTITY::GET_ENTITY_VELOCITY(playerVehicle);
				float playerVelocityX = playerVelocity.x;
				float playerVelocityY = playerVelocity.y;
				float playerVelocityZ = playerVelocity.z;
				if (VEHICLE::IS_VEHICLE_IN_GARAGE_AREA((char*)garage.c_str(), playerVehicle))
				{
					if (playerVelocityX < 0.1f && playerVelocityY < 0.1f && playerVelocityZ < 0.1f)
					{
						if (!PLAYER::IS_WANTED_AND_HAS_BEEN_SEEN_BY_COPS(PLAYER::PLAYER_PED_ID()))
						{
							if (VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 13 || // Cycles
								VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 14 || // Boats
								VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 15 || // Helicopters
								VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 16 || // Planes
								VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 18 || // Emergency
								VEHICLE::GET_VEHICLE_CLASS(playerVehicle) == 19)   // Military
							{
								// I ant touchin that
							}
							else
							{
								ResprayVehicle(playerVehicle, doorName);
								while (VEHICLE::IS_VEHICLE_IN_GARAGE_AREA((char*)garage.c_str(), playerVehicle))
								{
									if (!PED::IS_PED_IN_ANY_VEHICLE(player, 0))
									{
										break;
									}
									WAIT(0);
								}
							}
						}
					}
				}
			}
			//worldtravel::HelpText::DisplayHelpText(doorName);
			
			/*if (PLAYER::GET_PLAYER_WANTED_LEVEL(playerPed) == 0)
			{
				OBJECT::DOOR_SYSTEM_SET_OPEN_RATIO(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 0.0f, false, false);
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 0, false, false);
			}
			else if (PLAYER::GET_PLAYER_WANTED_LEVEL(playerPed) > 0)
			{
				OBJECT::DOOR_SYSTEM_SET_OPEN_RATIO(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), -1.0f, false, false);
				OBJECT::DOOR_SYSTEM_SET_DOOR_STATE(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), 6, false, false);
			}*/
			

			
		}
		bool IsPayNSprayActive(std::string doorName)
		{
			return OBJECT::IS_DOOR_REGISTERED_WITH_SYSTEM(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()));
		}
		void DeactivatePayNSpray(std::string doorName)
		{
			OBJECT::REMOVE_DOOR_FROM_SYSTEM(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()));
		}
		void ActivatePayNSpray(std::string doorName, std::string doorObjName, float doorCoordX, float doorCoordY, float doorCoordZ)
		{
			OBJECT::ADD_DOOR_TO_SYSTEM(GAMEPLAY::GET_HASH_KEY((char*)doorName.c_str()), GAMEPLAY::GET_HASH_KEY((char*)doorObjName.c_str()), doorCoordX, doorCoordY, doorCoordZ, true, true, true);
		}
	}
}