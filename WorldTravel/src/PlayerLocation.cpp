#include "PlayerLocation.h"

namespace worldtravel
{
	int playerLocationID = 0; // 0 = LS    1 = LC    2 = NY    3 = CP

	void SetPlayerLocationID(int id)
	{
		playerLocationID = id;
	}
	int GetPlayerLocationID()
	{
		return playerLocationID;
	}

	bool IsSwitchingMaps()
	{
		return playerLocationID == -1;
	}

	bool IsLosSantos()
	{
		return playerLocationID == 0;
	}

	bool IsLibertyCity()
	{
		return playerLocationID == 1;
	}

	bool IsNorthYankton()
	{
		return playerLocationID == 2;
	}

	bool IsCayoPerico()
	{
		return playerLocationID == 3;
	}

	bool IsSantaFuegos()
	{
		return playerLocationID == 4;
	}
}