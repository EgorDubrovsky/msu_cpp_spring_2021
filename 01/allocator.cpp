#include "allocator.hpp"

Allocator::Allocator()
{
	totalSize = 0;
	usedSize = 0;
	memoryPtr = nullptr;
}

Allocator::~Allocator()
{
	if (memoryPtr != nullptr)
		delete []memoryPtr;
}

size_t Allocator::getTotalSize()
{
	return totalSize;
}

size_t Allocator::getUsedSize()
{
	return usedSize;
}

char *Allocator::getMemoryPtr()
{
	return memoryPtr;
}


void Allocator::makeAllocator(size_t maxSize)
{
	if (memoryPtr == nullptr)
	{
		totalSize = maxSize;
		memoryPtr = new char[maxSize];
	}
	else
	{
		totalSize = maxSize;
		usedSize = 0;
		delete []memoryPtr;
		memoryPtr = new char[maxSize];
	}
}

char* Allocator::alloc(size_t size)
{
	if (usedSize + size <= totalSize)
	{
		usedSize += size;
		return memoryPtr + (usedSize - size);
	}
	else 
		return nullptr;
}

void Allocator::reset()
{
	usedSize = 0;
}
