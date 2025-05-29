#include "RestrictedAreaClearance.h"

namespace worldtravel {
	namespace RestrictedAreaClearance {
		bool restrictedAreaClearance;
		bool HasRestrictedAreaClearance()
		{
			return restrictedAreaClearance;
		}
		void GetRestrictedAreaClearanceFromIni()
		{
			restrictedAreaClearance = Settings::GrantAccessToRestrictedAreas;
		}

		void SetRestrictedAreaClearance(bool clearance)
		{
			restrictedAreaClearance = clearance;
		}
	}
}