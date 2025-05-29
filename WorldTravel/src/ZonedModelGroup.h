
#include "ZonedModel.h"
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;
#ifndef ZONEDMODELGROUP
#define ZONEDMODELGROUP
class ZonedModelGroup
{
public:
	std::vector<ZonedModel> groupZonedModel;
	std::vector<std::string> groupZonedModelNames;


	void ReadFile(const std::string& filePath);
	void SuppressZonedModels(bool suppressZonedModels, bool type);
};
#endif
