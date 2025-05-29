// Taken from the CitizenFX project: https://github.com/citizenfx/fivem/blob/84444fe5a722acb14b3d33bd85f3352871caf0ab/code/client/shared/Hooking.Stubs.cpp
#include "Hooking.h"
#include "Hooking.Stubs.h"
#include <MinHook.h>
#include <cassert>

namespace hook
{
	void trampoline_raw(void* address, const void* target, void** origTrampoline)
	{
		static auto mhInitializer = ([] {
			return MH_Initialize();
			})();

		auto location = reinterpret_cast<void*>(hook::get_adjusted(address));
		MH_CreateHook(location, const_cast<void*>(target), origTrampoline);
		auto status = MH_EnableHook(location);
		assert(status == MH_OK);
	}
}