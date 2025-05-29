#include "Settings.h"
#include <stdio.h>

bool Settings::EnableLogging = true;
bool Settings::FastTravel = true;
int Settings::TeleportKey = VK_F11;
bool Settings::EnableLibertyCity = true;
bool Settings::EnableCayoPerico = true;
bool Settings::EnableNorthYankton = true;
bool Settings::EnableSantaFuegos = true;
bool Settings::EnableLibertyCityLODLights = true;
bool Settings::EnableLCOnStartup = true;
bool Settings::GrantAccessToRestrictedAreas = false;
// Liberty City
float Settings::LC_X = 4976.62f;
float Settings::LC_Y = -2914.04f;
float Settings::LC_Z = 16.48f;
// North Yankton
float Settings::NY_X = 3359.87f;
float Settings::NY_Y = -4849.52f;
float Settings::NY_Z = 111.67f;
// Cayo Perico
float Settings::CP_X = 4906.26f;
float Settings::CP_Y = -4912.76f;
float Settings::CP_Z = 3.36f;
// Los Santos
float Settings::LS_X = 272.17f;
float Settings::LS_Y = -616.54f;
float Settings::LS_Z = 35.16f;
// Santa Fuegos
float Settings::SF_X = 3359.87f;
float Settings::SF_Y = -4849.52f;
float Settings::SF_Z = 111.67f;



void Settings::Load()
{
    char iniFilePath[MAX_PATH];
    GetFullPathName("WorldTravel.ini", MAX_PATH, iniFilePath, nullptr);

    EnableLogging = LoadBoolSetting("WorldTravel", "EnableLogging", true, iniFilePath);
    FastTravel = LoadBoolSetting("WorldTravel", "FastTravel", true, iniFilePath);
    TeleportKey = LoadIntSetting("WorldTravel", "TeleportKey", VK_F11, iniFilePath);
    EnableLibertyCity = LoadBoolSetting("WorldTravel", "EnableLibertyCity", true, iniFilePath);
    EnableCayoPerico = LoadBoolSetting("WorldTravel", "EnableCayoPerico", true, iniFilePath);
    EnableNorthYankton = LoadBoolSetting("WorldTravel", "EnableNorthYankton", true, iniFilePath);
    EnableSantaFuegos = LoadBoolSetting("WorldTravel", "EnableSantaFuegos", true, iniFilePath);
	EnableLibertyCityLODLights = LoadBoolSetting("WorldTravel", "EnableLibertyCityLODLights", true, iniFilePath);
	EnableLCOnStartup = LoadBoolSetting("WorldTravel", "EnableLCOnStartup", false, iniFilePath);
    GrantAccessToRestrictedAreas = LoadBoolSetting("WorldTravel", "AccessRestrictedAreas", false, iniFilePath);

    ParseCoords("Teleport_LibertyCity", "Coords", 4976.62f, -2914.04f, 16.48f, LC_X, LC_Y, LC_Z, iniFilePath);
    ParseCoords("Teleport_NorthYankton", "Coords", 3359.87f, -4849.52f, 111.67f, NY_X, NY_Y, NY_Z, iniFilePath);
    ParseCoords("Teleport_CayoPerico", "Coords", 4906.26f, -4912.76f, 3.36f, CP_X, CP_Y, CP_Z, iniFilePath);
    ParseCoords("Teleport_LosSantos", "Coords", -272.17f, -616.54f, 35.16f, LS_X, LS_Y, LS_Z, iniFilePath);
    ParseCoords("Teleport_SantaFuegos", "Coords", 552.87f, -4351.54f, 40.39f, SF_X, SF_Y, SF_Z, iniFilePath);

}

// Settings helper functions
bool Settings::LoadBoolSetting(const char* section, const char* key, bool defaultValue, const char* iniFilePath)
{
    UINT value = GetPrivateProfileInt(section, key, defaultValue ? 1 : 0, iniFilePath);
    return value != 0;
}

int Settings::LoadIntSetting(const char* section, const char* key, int defaultValue, const char* iniFilePath)
{
    return GetPrivateProfileInt(section, key, defaultValue, iniFilePath);
}

float Settings::LoadFloatSetting(const char* section, const char* key, float defaultValue, const char* iniFilePath)
{
    char buffer[32];
    GetPrivateProfileString(section, key, "", buffer, sizeof(buffer), iniFilePath);
    if (strlen(buffer) == 0)
        return defaultValue;
    return static_cast<float>(atof(buffer));
}

void Settings::ParseCoords(const char* section, const char* key,
    float defaultX, float defaultY, float defaultZ,
    float& outX, float& outY, float& outZ,
    const char* iniFilePath)
{
    char buffer[128];
    GetPrivateProfileString(section, key, "", buffer, sizeof(buffer), iniFilePath);

    if (strlen(buffer) == 0)
    {
        outX = defaultX;
        outY = defaultY;
        outZ = defaultZ;
        return;
    }

    float x = defaultX, y = defaultY, z = defaultZ;
    if (sscanf_s(buffer, "%f,%f,%f", &x, &y, &z) == 3)
    {
        outX = x;
        outY = y;
        outZ = z;
    }
    else
    {
        // fallback if parsing fails
        outX = defaultX;
        outY = defaultY;
        outZ = defaultZ;
    }
}