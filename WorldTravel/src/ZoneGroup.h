
#include "Zone.h"
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;
#ifndef MAPZONEGROUP
#define MAPZONEGROUP
class ZoneGroup
{
public:
	std::vector<Zone> groupZones;
	std::vector<std::string> groupZoneNames;


	void ReadFile(const std::string& filePath);
	void EnableZoneGroup();
	void DisableZoneGroup();
};
#endif
