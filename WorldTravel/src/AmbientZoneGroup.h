#include "AmbientZone.h"
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;
#ifndef AMBIENTZONEGROUP
#define AMBIENTZONEGROUP
class AmbientZoneGroup
{
public:
	std::vector<AmbientZone> groupAmbientZone;
	std::vector<std::string> groupAmbientZoneNames;


	void ReadFile(const std::string& filePath);
	void RequestAmbientZoneGroup(bool checkState);
	void RequestAmbientZoneGroupIfNotActive();
	void RemoveAmbientZoneGroup(bool checkState);
	void RemoveAmbientZoneGroupIfActive();
};
#endif
