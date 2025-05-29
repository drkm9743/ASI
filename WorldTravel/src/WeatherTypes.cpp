#include "WeatherTypes.h"

void WeatherTypes::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, weatherTypeNames);

}

void WeatherTypes::SetWeatherType()
{
	int weatherID = std::rand() % weatherTypeNames.size();
	GAMEPLAY::SET_OVERRIDE_WEATHER(const_cast<char*>(weatherTypeNames[weatherID].c_str()));
	if (!NETWORK::NETWORK_IS_IN_SESSION())
	{
		GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST(const_cast<char*>(weatherTypeNames[weatherID].c_str()));
	}
	else
	{
		GAMEPLAY::SET_WEATHER_TYPE_PERSIST(const_cast<char*>(weatherTypeNames[weatherID].c_str()));
	}
}

void WeatherTypes::ResetWeatherType(bool loadNewWeatherBeforeReset)
{
	// if in multiplayer
	if (NETWORK::NETWORK_IS_IN_SESSION())
	{
		if (loadNewWeatherBeforeReset)
		{
			int weatherID = std::rand() % weatherTypeNames.size();
			GAMEPLAY::SET_WEATHER_TYPE_NOW(const_cast<char*>(weatherTypeNames[weatherID].c_str()));
		}
		GAMEPLAY::CLEAR_WEATHER_TYPE_NOW_PERSIST_NETWORK(1);
	}
	else
	{
		if (loadNewWeatherBeforeReset)
		{
			int weatherID = std::rand() % weatherTypeNames.size();
			GAMEPLAY::SET_WEATHER_TYPE_PERSIST(const_cast<char*>(weatherTypeNames[weatherID].c_str()));
		}
		GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
	}

	GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
}