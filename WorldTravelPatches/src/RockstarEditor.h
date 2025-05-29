#pragma once
#include <cstdint>
#include <string>
#include <MinHook.h>
#include "Hooking.h"

// Taken from Cfx.Re https://github.com/citizenfx/fivem/blob/master/code/components/gta-streaming-five/src/PatchReplayLimits.cpp
class RockstarEditor
{
public:

	struct PatternPair
	{
		std::string_view pattern;
		int offset;
	};

	static void PatchRockstarEditorRelocateRelative(void* base, std::initializer_list<PatternPair> list)
	{
		void* oldAddress = nullptr;

		for (auto& entry : list)
		{
			auto location = hook::get_pattern<int32_t>(entry.pattern, entry.offset);

			if (!oldAddress)
			{
				oldAddress = hook::get_address<void*>(location, 0, 4/*entry.operand_remaining*/);
			}

			auto curTarget = hook::get_address<void*>(location, 0, 4/*entry.operand_remaining*/);
			assert(curTarget == oldAddress);

			hook::put<int32_t>(location, static_cast<int32_t>((intptr_t)base - (intptr_t)location - 4 /*entry.operand_remaining*/));
		}
	}

	static void Patch()
	{
		static constexpr uint32_t NewBufferSize = 4096;
		static void* NewIPLBuffer;

		NewIPLBuffer = hook::AllocateStubMemory(sizeof(uint32_t) * NewBufferSize);

		// CPacketIPL seems to be deprecated and CPacketIPL2 was added instead
		// Relocate CPacketIPL2 buffer references; stubs from 3258
		PatchRockstarEditorRelocateRelative(NewIPLBuffer, {
			{ "48 8D 15 ? ? ? ? 48 8D 4C 24 ? 48 89 5C 24 ? 89 5C 24 ? E8 ? ? ? ? 48 8D 54 24", 3 }, // ReplayIPLManager::Process
			{ "48 8D 0D ? ? ? ? 49 C1 E0 ? E8 ? ? ? ? 89 1D", 3 }                                    // ReplayIPLManager::SubmitNewIPLData
			});

		// Update offsets and fields
		hook::put<uint32_t>(hook::get_pattern("BB ? ? ? ? 41 8B D6 48 8B CE E8 ? ? ? ? 89 18 40 38 3D", 1), (36 + (NewBufferSize * 4 * 2))); // CReplayMgrInternal::CalculateSizeOfBlock
		hook::put<uint32_t>(hook::get_pattern("B9 22 01 00 00 48 8B D7", 1), NewBufferSize);  // CPacketExtension::CloneExt


		// disables stupid watermark at beginning of rockstar editor render, credit to ranstar74.
		// WatermarkRenderer::Render
		uint8_t* renderWatermark = hook::get_pattern<uint8_t>("48 83 EC ? 8B 0D ? ? ? ? 65 48 8B 04 25 ? ? ? ? BA ? ? ? ? 48 8B 04 C8 8B 0C 02 D1 E9 F6 C1 ? 74 ? 83 3D");
		DWORD oldProtect;
		VirtualProtect(renderWatermark, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
		*renderWatermark = 0xC3; // ret
		VirtualProtect(renderWatermark, 1, oldProtect, &oldProtect);
	};
};