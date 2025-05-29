// Taken from the CitizenFX project: https://github.com/citizenfx/fivem/blob/84444fe5a722acb14b3d33bd85f3352871caf0ab/code/client/shared/Hooking.Stubs.h
#pragma once

namespace hook
{
	extern void trampoline_raw(void* address, const void* target, void** origTrampoline);

	template<typename TFunc, typename TAddr>
	TFunc* trampoline(TAddr address, TFunc* target)
	{
		TFunc* orig = nullptr;
		trampoline_raw(address, target, (void**)&orig);

		return orig;
	}
}