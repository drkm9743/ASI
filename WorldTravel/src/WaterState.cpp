#include "WaterState.h"


namespace worldtravel {
	namespace WaterState {
		int state = 0;
		int GetWaterState()
		{
			return state;
		}
		void SetWaterState(int s)
		{
			STREAMING::LOAD_GLOBAL_WATER_FILE(s);
			state = s;
		}
	}
}