#include "Zone.h"

using namespace std;



std::string Zone::GetZoneName()
{
	return zoneName;
}
void Zone::SetZoneName(const std::string& zone)
{
	zoneName = zone;
	zoneId = ZONE::GET_ZONE_FROM_NAME_ID(const_cast<char*>(zoneName.c_str()));
}

int Zone::GetZoneId()
{
	return zoneId;
}

void Zone::EnableZone()
{
	ZONE::SET_ZONE_ENABLED(zoneId, true);
}
void Zone::DisableZone()
{
	ZONE::SET_ZONE_ENABLED(zoneId, false);
}