#pragma once
#include <stdint.h>

// Unused currently

class CPathFind
{
public:
	virtual ~CPathFind() = 0;
	virtual uint32_t* Register(uint32_t* outIndex, const char* name) = 0;
	virtual uint32_t* FindSlot(uint32_t* outIndex, const char* name) = 0;
	virtual void Remove(uint32_t index) = 0;
	virtual void RemoveSlot(uint32_t index) = 0;
	virtual bool Load(uint32_t index, void* region, uint32_t memSize) = 0;

	uint32_t GetBaseIndex();
	bool DoesKeepPathNodesInMemory();
	void SetKeepPathNodesInMemory(bool value);

	static CPathFind* Instance();
};

