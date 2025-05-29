#include "ZonedModelGroup.h"




void ZonedModelGroup::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, groupZonedModelNames);
	for (int i = 0; i < groupZonedModelNames.size(); i++)
	{
		ZonedModel temp;
		groupZonedModel.push_back(temp);
		groupZonedModel[i].SetZonedModelName(groupZonedModelNames[i]);
	}
}
void ZonedModelGroup::SuppressZonedModels(bool suppressZonedModel, bool type)
{
	for (int i = 0; i < groupZonedModelNames.size(); i++)
	{
		groupZonedModel[i].SetZonedModelSuppressed(suppressZonedModel, type);
	}
}