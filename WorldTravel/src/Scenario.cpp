#include "Scenario.h"

using namespace std;



std::string Scenario::GetScenarioName()
{
	return scenarioName;
}

void Scenario::SetScenarioName(const std::string& scenario)
{
	scenarioName = scenario;
	scenarioState = AI::IS_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str());
}



bool Scenario::GetScenarioState()
{
	return scenarioState;
}

void Scenario::SetScenarioState()
{
	scenarioState = AI::IS_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str());
}

void Scenario::SetScenarioState(bool state)
{
	scenarioState = state;
}



void Scenario::RequestScenario(bool checkState)
{
	if (checkState)
	{
		if (!scenarioState)
		{
			return;
		}
	}
	AI::SET_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str(), true);
}

void Scenario::RequestScenarioIfNotActive()
{
	if (!AI::IS_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str()))
	{
		AI::SET_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str(), true);
	}
}



void Scenario::RemoveScenario(bool saveState)
{
	if (saveState)
		SetScenarioState();
	AI::SET_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str(), false);
}

void Scenario::RemoveScenarioIfActive()
{
	if (AI::IS_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str()))
	{
		AI::SET_SCENARIO_GROUP_ENABLED((char*)scenarioName.c_str(), false);
	}
}