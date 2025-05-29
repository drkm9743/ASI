#pragma once
#include <vector>
#include <functional>

class Events
{
public:
    class Event
    {
    public:
        using Callback = std::function<void(void)>;

        void Add(const Callback& cb);
        void Raise();

    private:
        std::vector<Callback> m_Callbacks;
    };

    static void Install();

    static Event OnCorePreUpdate;

private:
    static void HookGameSkeletonUpdate();
    static void(*gameSkeleton_RunUpdate_orig)(void* skeleton, int type);
    static void gameSkeleton_RunUpdate_detour(void* skeleton, int type);
};