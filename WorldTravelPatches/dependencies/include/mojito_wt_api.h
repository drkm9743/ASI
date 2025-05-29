#pragma once
#include "natives_hooks.h"
#include <functional>


namespace mojito
{
	void Init();
	void InstallGameSkelHook(std::function<void()> fn);
}

namespace mjextracontent
{
	void ExecuteContentChangeSetGroup(unsigned contentNameHash, unsigned changeSetGroupHash);
	void ExecuteContentChangeSetGroup(const char* contentName, const char* changeSetGroupName);
	void RevertContentChangeSetGroup(unsigned contentNameHash, unsigned changeSetGroupHash);
	void RevertContentChangeSetGroup(const char* contentName, const char* changeSetGroupName);
}

namespace mjworldtravel
{
	void SetWaterClipRect(int xMin, int yMin, int xMax, int yMax);
	void LoadWater(const char* fileName);
	void ResetWater();
}

