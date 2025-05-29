#include "Hooking.Patterns.h"
#include "Hooking.h"
#include <MinHook.h>
#include "PlayerLocation.h"
#include "GameVersion.h"

static void (*gImpl_CFogVolumeMgr_RenderFogVolume)(void* self, float* FogVolumeParams[4]);
static void lcImpl_CFogVolumeMgr_RenderFogVolume(void* self, float* FogVolumeParams[4])
{
	if (worldtravel::gameversion::GetGameVersion()) // Enhanced
	{
		return;
	}
	else // Legacy
	{
		if (!worldtravel::IsLibertyCity())
			gImpl_CFogVolumeMgr_RenderFogVolume(self, FogVolumeParams);
		else
			return;
	}
}

void ToggleFogVolumeOff()
{
	if (worldtravel::gameversion::GetGameVersion()) // Enhanced
	{

	}
	else // Legacy
	{
		auto location = hook::get_pattern("48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 55 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC 20 02 00 00 0F 29 70 ? 0F 29 78 ? 48 8B D9");
		MH_CreateHook(location, lcImpl_CFogVolumeMgr_RenderFogVolume, (void**)&gImpl_CFogVolumeMgr_RenderFogVolume);
		MH_EnableHook(location);
	}
}