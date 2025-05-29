#include "AmbientZoneGroup.h"
using namespace std;





void AmbientZoneGroup::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, groupAmbientZoneNames);
	for (int i = 0; i < groupAmbientZoneNames.size(); i++)
	{
		AmbientZone temp;
		groupAmbientZone.push_back(temp);
		groupAmbientZone[i].SetAmbientZoneName(groupAmbientZoneNames[i]);
	}

}



void AmbientZoneGroup::RequestAmbientZoneGroup(bool checkState)
{
	for (int i = 0; i < groupAmbientZoneNames.size(); i++)
	{
		groupAmbientZone[i].RequestAmbientZone(checkState);
	}
}

void AmbientZoneGroup::RequestAmbientZoneGroupIfNotActive()
{
	for (int i = 0; i < groupAmbientZoneNames.size(); i++)
	{
		groupAmbientZone[i].RequestAmbientZoneIfNotActive();
	}
}



void AmbientZoneGroup::RemoveAmbientZoneGroup(bool checkState)
{
	for (int i = 0; i < groupAmbientZone.size(); i++)
	{
		groupAmbientZone[i].RemoveAmbientZone(checkState);
	}
}

void AmbientZoneGroup::RemoveAmbientZoneGroupIfActive()
{
	for (int i = 0; i < groupAmbientZoneNames.size(); i++)
	{
		groupAmbientZone[i].RemoveAmbientZoneIfActive();
	}
}