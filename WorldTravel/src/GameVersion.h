#pragma once
#include <iostream>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")

namespace worldtravel
{
    namespace gameversion
    {
        void SetGameVersion();

        bool GetGameVersion();
    }
}