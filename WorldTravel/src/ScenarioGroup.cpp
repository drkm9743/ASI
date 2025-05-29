#include "ScenarioGroup.h"
using namespace std;





void ScenarioGroup::ReadFile(const std::string& filePath)
{
	worldtravel::file::readFileToVector(filePath, groupScenarioNames);
	for (int i = 0; i < groupScenarioNames.size(); i++)
	{
		Scenario temp;
		groupScenarios.push_back(temp);
		groupScenarios[i].SetScenarioName(groupScenarioNames[i]);
	}

}



void ScenarioGroup::RequestScenarioGroup(bool checkState)
{
	for (int i = 0; i < groupScenarioNames.size(); i++)
	{
		groupScenarios[i].RequestScenario(checkState);
	}
}

void ScenarioGroup::RequestScenarioGroupIfNotActive()
{
	for (int i = 0; i < groupScenarioNames.size(); i++)
	{
		groupScenarios[i].RequestScenarioIfNotActive();
	}
}



void ScenarioGroup::RemoveScenarioGroup(bool checkState)
{
	for (int i = 0; i < groupScenarioNames.size(); i++)
	{
		groupScenarios[i].RemoveScenario(checkState);
	}
}

void ScenarioGroup::RemoveScenarioGroupIfActive()
{
	for (int i = 0; i < groupScenarioNames.size(); i++)
	{
		groupScenarios[i].RemoveScenarioIfActive();
	}
}