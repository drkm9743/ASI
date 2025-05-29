#pragma once
#include "eWaterArea.h"
#include <cstdint>
#include "Hooking.h"
#include "Hooking.Patterns.h"

class CWaterData
{
public:
	static inline int32_t
		* bd_min_x,
		* bd_min_y,
		* bd_max_x,
		* bd_max_y;
	static inline eWaterArea* curLoadedArea;
public:
	static void switchWater(eWaterArea waterArea);
	static inline void load(void* path)
	{
		//75 30 C6 05
		static void(*fn)(void*) = (decltype(fn))hook::get_pattern("48 83 EC 28 80 3D ? ? ? ? ? 75 30 C6 05"); // Water::LoadWater

		fn(path);
	}
	static inline void unload()
	{
		//40 53 48 83 EC 20 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 48 89 1D ? ? ? ? 89 1D ? ? ? ? E8 ? ? ? ? 48 8B 0D
		//40 53 48 83 EC 20 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 48 89 1D ? ? ? ? 89 1D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 89 1D ? ? ? ? 89 1D
		static void(*fn)() = (decltype(fn))hook::pattern("40 53 48 83 EC 20 48 8B 0D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 DB 48 89 1D ? ? ? ? 89 1D ? ? ? ? E8 ? ? ? ? 48 8B 0D ? ? ? ? 48 89 1D ? ? ? ? 89 1D ? ? ? ? E8 ? ? ? ? 48 89 1D ? ? ? ? 89 1D ? ? ? ? 89 1D").count(3).get(0).get<void*>(0); // ResetWater

		fn();
	}
};