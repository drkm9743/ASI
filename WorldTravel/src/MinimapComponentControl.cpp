#include "MinimapComponentControl.h"
#include "Hooking.h"
#include "Hooking.Patterns.h"
#include <cstring>
#include <MinHook.h>

struct MinimapData
{
	char name[100];
	float posX;
	float posY;
	float sizeX;
	float sizeY;
	char alignX;
	char alignY;
	char pad[2];
};

static MinimapData* minimapArray = nullptr;
static constexpr int minimapEntries = 11;
static MinimapData minimapBackup[minimapEntries];

void InitMinimapComponentControl()
{
	auto location = hook::get_pattern("48 8D 54 24 38 41 B8 64 00 00 00 48 8B 48 08 48 8D 05", 18);
	minimapArray = hook::get_address<MinimapData*>(location);

	if (minimapArray)
		memcpy(minimapBackup, minimapArray, sizeof(minimapBackup));
}

void SetMinimapComponentPosition(const char* name, const char* alignX, const char* alignY,
                                 float posX, float posY, float sizeX, float sizeY)
{
	if (!minimapArray) return;

	for (int i = 0; i < minimapEntries; ++i)
	{
		MinimapData* entry = &minimapArray[i];

		if (_stricmp(entry->name, name) == 0)
		{
			entry->alignX = alignX[0];
			entry->alignY = alignY[0];
			entry->posX = posX;
			entry->posY = posY;
			entry->sizeX = sizeX;
			entry->sizeY = sizeY;
			break;
		}
	}
}

void RestoreMinimapComponents()
{
	if (minimapArray)
		memcpy(minimapArray, minimapBackup, sizeof(minimapBackup));
}

#include "..\dependencies\include\nativeCaller.h"

void RegisterMinimapNatives()
{
	REGISTER_NATIVE("SET_MINIMAP_COMPONENT_POSITION", [](scrNativeCallContext* context)
	{
		const char* name   = context->GetArgument<const char*>(0);
		const char* alignX = context->GetArgument<const char*>(1);
		const char* alignY = context->GetArgument<const char*>(2);
		float posX         = context->GetArgument<float>(3);
		float posY         = context->GetArgument<float>(4);
		float sizeX        = context->GetArgument<float>(5);
		float sizeY        = context->GetArgument<float>(6);

		SetMinimapComponentPosition(name, alignX, alignY, posX, posY, sizeX, sizeY);
	});
}
