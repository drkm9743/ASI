#include "ZoneGroup.h"
using namespace std;





void ZoneGroup::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, groupZoneNames);
	for (int i = 0; i < groupZoneNames.size(); i++)
	{
		Zone temp;
		groupZones.push_back(temp);
		groupZones[i].SetZoneName(groupZoneNames[i]);
	}

}


void ZoneGroup::EnableZoneGroup()
{
	for (int i = 0; i < groupZones.size(); i++)
	{
		groupZones[i].EnableZone();
	}
}
void ZoneGroup::DisableZoneGroup()
{
	for (int i = 0; i < groupZones.size(); i++)
	{
		groupZones[i].DisableZone();
	}
}