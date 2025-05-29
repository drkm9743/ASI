#pragma once

class Water
{
public:
    static void Init();
    static void Load(const char* filePath);
    static void BeginLoadScreen();
    static void EndLoadScreen();

private:
    static void CheckForLoading();

    static inline bool wantToLoadWaterData = false;
    static inline char waterDataFileToLoad[512] = {};
    static inline unsigned int* gameState = nullptr;
    static inline unsigned int prevGameState = 0xFFFFFFFF;

    using tCWaterData_Unload = void(*)();
    using tCWaterData_Load = void(*)(const char* path);

    static inline tCWaterData_Unload fCWaterData_Unload = nullptr;
    static inline tCWaterData_Load fCWaterData_Load = nullptr;
};