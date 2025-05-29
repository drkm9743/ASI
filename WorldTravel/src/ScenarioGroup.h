
#include "Scenario.h"
#include <string>
#include <vector>
#include "FileReader.h"

using namespace std;
#ifndef SCENARIOGROUP
#define SCENARIOGROUP
class ScenarioGroup
{
public:
	std::vector<Scenario> groupScenarios;
	std::vector<std::string> groupScenarioNames;


	void ReadFile(const std::string& filePath);
	void RequestScenarioGroup(bool checkState);
	void RequestScenarioGroupIfNotActive();
	void RemoveScenarioGroup(bool checkState);
	void RemoveScenarioGroupIfActive();
};
#endif
