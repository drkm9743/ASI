#include "CPathFind.h"
#include "Hooking.Patterns.h"

// Unused currently

uint32_t CPathFind::GetBaseIndex()
{
	return *(uint32_t*)((uint8_t*)this + 0x8);
}

bool CPathFind::DoesKeepPathNodesInMemory()
{
	return *(bool*)((uint8_t*)this + 0x4BE4);
}

void CPathFind::SetKeepPathNodesInMemory(bool value)
{
	*(bool*)((uint8_t*)this + 0x4BE4) = value;
}

CPathFind* CPathFind::Instance()
{
	static CPathFind* inst = []() 
	{
		auto addr = hook::get_pattern<char>("48 8D 0D ? ? ? ? 8B D7 E8 ? ? ? ? 48 83 64 24 ? ?"); // ThePaths, qword_1428B2A70
		return (CPathFind*)(addr + *(int*)(addr + 3) + 7);
	}();

	return inst;
}