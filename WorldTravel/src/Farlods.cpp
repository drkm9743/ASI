#include "Farlods.h"
#include "Hooking.Patterns.h"
#include <MinHook.h>
#include "GameVersion.h"

namespace patches {
	namespace farlods {

		struct Farlods
		{
			// if Enable && !CullEverything then draw the farlods
			bool Enable;                                 // 00
			bool CullEverything;                         // 01
			int8_t pad6[0x6];                            // 07
			int16_t SilhouettteShader;                   // 08
			int32_t SilhouettteDrawTech;                 // 10
			int32_t SilhouetteDrawWaterReflectionTech;   // 14
			int16_t HorizonObjectsDictionary;            // 18
			void* m_DrawablesDict;                       // 20
			struct // atArray<gtaDrawable*>
			{
				void** Elements;   // 00
				uint16_t Count;    // 08
				uint16_t Capacity; // 0A
				uint32_t pad4;     // 0C
			} m_Drawables;         // 10
			int8_t ArrayVisible[0xA];                    // 30
			float ScaleFactor;                           // 40
			int32_t DSS_Scene;                           // 44
			int32_t DSS_Water;                           // 48
			const float DepthRangePercentage;            // 4C
			const float FarPlane;                        // 50
			int8_t pad8[0x4];                            // 57
		} *g_Farlods;
		static_assert(sizeof(Farlods) == 0x58);


		bool g_visible = true;
		uint16_t g_origDrawablesCount = 0;
		void(*g_origFarlodsShutdown)(Farlods*, int);

		void Farlods_Shutdown_Hook(Farlods* farlods, int skelFuncType)
		{
			//Delete this if statement when Enhanced pattern is updated
			if (worldtravel::gameversion::GetGameVersion())
			{
				return;
			}

			if (!g_visible)
			{
				// restore count to avoid memory leaks
				g_Farlods->m_Drawables.Count = g_origDrawablesCount;
			}

			g_origFarlodsShutdown(farlods, skelFuncType);
		}

		void Init()
		{
			if (worldtravel::gameversion::GetGameVersion()) // Enhanced
			{

			}
			else // Legacy
			{
				uintptr_t addr = (uintptr_t)hook::get_pattern("48 8D 0D ? ? ? ? 89 44 24 38 89 44 24 30 89 44 24 28", 3); // CHorizonObjects::Render
				addr = addr + *(int*)addr + 4;
				g_Farlods = (Farlods*)addr;

				MH_Initialize();
				MH_CreateHook(hook::get_pattern("83 FA 01 0F 85 ? ? ? ? 48 89 5C 24 ? 48 89 74 24"), Farlods_Shutdown_Hook, (void**)&g_origFarlodsShutdown); // CHorizonObjects::Shutdown
				MH_EnableHook(MH_ALL_HOOKS);
			}
		}

		void SetVisible(bool visible)
		{
			if (visible == g_visible)
			{
				return;
			}

			g_visible = visible;

			//Delete this if statement when Enhanced pattern is updated
			if (worldtravel::gameversion::GetGameVersion())
			{
				return;
			}
			
			if (g_visible)
			{
				g_Farlods->m_Drawables.Count = g_origDrawablesCount;
			}
			else
			{
				g_origDrawablesCount = g_Farlods->m_Drawables.Count;
				g_Farlods->m_Drawables.Count = 0;
			}
		}

		bool AreVisible()
		{
			return g_visible;
		}

	}
}