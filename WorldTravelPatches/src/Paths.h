#pragma once
#include "CPathFind.h"
#include "CDataFileMgr.h"

// Unused Currently

class Paths
{
public:
    static void Init();
    static void SwitchPaths();

private:
    static void CheckForSwitch();
    template<int FramesToSkip = 1>
    static void LogStackTrace();
    static CDataFileMgr::DataFile* GetRpfFile(const char* filename);

    static uint32_t* CPathFind_Register_detour(CPathFind* pf, uint32_t* outIndex, const char* name);
    static bool CPathFind_PlaceResource_detour(CPathFind* pf, uint32_t index, void* resourceMap, void* resourceInfo);

    static inline bool wantsToSwitchPaths = false;
    static inline bool vanillaPaths = true;

    static inline uint32_t* (*CPathFind_Register_orig)(CPathFind* pf, uint32_t* outIndex, const char* name) = nullptr;
    static inline bool (*CPathFind_PlaceResource_orig)(CPathFind* pf, uint32_t index, void* resourceMap, void* resourceInfo) = nullptr;
};
