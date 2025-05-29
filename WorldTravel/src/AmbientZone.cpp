#include "AmbientZone.h"

using namespace std;



std::string AmbientZone::GetAmbientZoneName()
{
	return ambientZoneName;
}

void AmbientZone::SetAmbientZoneName(const std::string& ambientZone)
{
	ambientZoneName = ambientZone;
	ambientZoneState = AUDIO::IS_AMBIENT_ZONE_ENABLED(const_cast<char*>(ambientZoneName.c_str()));
}



bool AmbientZone::GetAmbientZoneState()
{
	return ambientZoneState;
}

void AmbientZone::SetAmbientZoneState()
{
	ambientZoneState = AUDIO::IS_AMBIENT_ZONE_ENABLED(const_cast<char*>(ambientZoneName.c_str()));
}

void AmbientZone::SetAmbientZoneState(bool state)
{
	ambientZoneState = state;
}



void AmbientZone::RequestAmbientZone(bool checkState)
{
	if (checkState)
	{
		if (!ambientZoneState)
		{
			return;
		}
	}
	AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT(const_cast<char*>(ambientZoneName.c_str()), true, true);
}

void AmbientZone::RequestAmbientZoneIfNotActive()
{
	if (!AUDIO::IS_AMBIENT_ZONE_ENABLED(const_cast<char*>(ambientZoneName.c_str())))
	{
		AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT(const_cast<char*>(ambientZoneName.c_str()), true, true);
	}
}



void AmbientZone::RemoveAmbientZone(bool saveState)
{
	if (saveState)
		SetAmbientZoneState();
	AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT(const_cast<char*>(ambientZoneName.c_str()), false, true);
}

void AmbientZone::RemoveAmbientZoneIfActive()
{
	if (AUDIO::IS_AMBIENT_ZONE_ENABLED(const_cast<char*>(ambientZoneName.c_str())))
	{
		AUDIO::SET_AMBIENT_ZONE_STATE_PERSISTENT(const_cast<char*>(ambientZoneName.c_str()), false, true);
	}
}