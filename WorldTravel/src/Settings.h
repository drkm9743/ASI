#pragma once
#include <Windows.h>

class Settings
{
public:
    static bool EnableLogging;
    static bool FastTravel;
    static int TeleportKey;
    static bool EnableCayoPerico;
    static bool EnableNorthYankton;
	static bool EnableLibertyCityLODLights;
	static bool EnableLCOnStartup;
    static bool GrantAccessToRestrictedAreas;

    static void Load();

private:
    static bool LoadBoolSetting(const char* section, const char* key, bool defaultValue, const char* iniFilePath);
    static int LoadIntSetting(const char* section, const char* key, int defaultValue, const char* iniFilePath);
};