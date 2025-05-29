#include "Events.h"
#include <MinHook.h>
#include "Hooking.Patterns.h"

Events::Event Events::OnCorePreUpdate;
void (*Events::gameSkeleton_RunUpdate_orig)(void* skeleton, int type) = nullptr;

void Events::Event::Add(const Callback& cb)
{
    m_Callbacks.push_back(cb);
}

void Events::Event::Raise()
{
    for (auto& cb : m_Callbacks)
    {
        cb();
    }
}

void Events::gameSkeleton_RunUpdate_detour(void* skeleton, int type)
{
    if (type == 1) // == Core
    {
        OnCorePreUpdate.Raise();
    }

    gameSkeleton_RunUpdate_orig(skeleton, type);
}

void Events::Install()
{
    HookGameSkeletonUpdate();
}

void Events::HookGameSkeletonUpdate()
{
    MH_CreateHook(hook::get_pattern("40 53 48 83 EC 20 48 8B 81 ? ? ? ? 48 85 C0 74 2A"),
        gameSkeleton_RunUpdate_detour,
        (void**)&gameSkeleton_RunUpdate_orig);
}
