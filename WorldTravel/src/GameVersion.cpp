#include "GameVersion.h"

namespace worldtravel
{
    namespace gameversion
    {
        bool GTAVEnhanced;
        bool initialize = false;

        void SetGameVersion()
        {
            char path[MAX_PATH];
            char* pszFile;
            HMODULE hModule = GetModuleHandleA(NULL);
            if (GetModuleFileNameA(hModule, path, MAX_PATH) != 0)
            {
                pszFile = PathFindFileName(path);
                if (strcmp(pszFile, "GTA5.exe") == 0)
                {
                    GTAVEnhanced = false;
                }
                else
                {
                    GTAVEnhanced = true;
                }
            }
            initialize = true;
        }

        bool GetGameVersion()
        {
            if (!initialize)
            {
                SetGameVersion();
            }
            return GTAVEnhanced;
        }
    }
}