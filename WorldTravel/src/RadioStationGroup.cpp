#include "RadioStationGroup.h"
using namespace std;





void RadioStationGroup::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, groupRadioStationNames);
	for (int i = 0; i < groupRadioStationNames.size(); i++)
	{
		RadioStation temp;
		groupRadioStations.push_back(temp);
		groupRadioStations[i].SetRadioStationName(groupRadioStationNames[i]);
	}

}


void RadioStationGroup::EnableRadioStationGroup()
{
	for (int i = 0; i < groupRadioStations.size(); i++)
	{
		groupRadioStations[i].EnableRadioStation();
	}
}
void RadioStationGroup::DisableRadioStationGroup()
{
	for (int i = 0; i < groupRadioStations.size(); i++)
	{
		groupRadioStations[i].DisableRadioStation();
	}
}