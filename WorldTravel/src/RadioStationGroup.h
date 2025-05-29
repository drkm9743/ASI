
#include "RadioStation.h"
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;
#ifndef RADIOSTATIONGROUP
#define RADIOSTATIONGROUP
class RadioStationGroup
{
public:
	std::vector<RadioStation> groupRadioStations;
	std::vector<std::string> groupRadioStationNames;


	void ReadFile(const std::string& filePath);
	void EnableRadioStationGroup();
	void DisableRadioStationGroup();
};
#endif
