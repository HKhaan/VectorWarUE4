#pragma once

#include <vector>
#include <list>
#include <functional>

class VirtualMemory
{
public:
	static std::vector<char> memory;
	static int memorySize;

	template <typename ContainerType>
	static ContainerType* NewStruct()
	{
		auto beginPos = memorySize;
		auto size = sizeof(ContainerType);
		memory.resize(memorySize + size);
		memorySize += size;
		auto obj = &memory[0] + beginPos;
		void* defaultValue = new ContainerType();
		memcpy(obj, defaultValue, size);
		delete defaultValue;
		auto retObj = (ContainerType*)(obj);
		return retObj;
	}

	static std::list<std::function<void()>> pointerFixCallbacks;
};
