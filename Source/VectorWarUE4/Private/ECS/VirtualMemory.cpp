#include "VirtualMemory.h"


std::vector<char> VirtualMemory::memory;
int VirtualMemory::memorySize;
std::list<std::function<void()>> VirtualMemory::pointerFixCallbacks;

