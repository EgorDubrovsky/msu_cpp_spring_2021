#include <iostream>
#include <cstdlib>

class Allocator
{
	size_t totalSize;
	size_t usedSize;
	char *memoryPtr;
	bool memoryIsAllocated;
public:
	Allocator();
	~Allocator();
	size_t getTotalSize();
	size_t getUsedSize();
	char *getMemoryPtr();
	void makeAllocator(size_t maxSize);
	char* alloc(size_t size);
	void reset();
};

Allocator::Allocator()
{
	totalSize = 0;
	usedSize = 0;
	memoryPtr = nullptr;
	memoryIsAllocated = false;
}

Allocator::~Allocator()
{
	if (memoryIsAllocated)
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
	if (!memoryIsAllocated)
	{
		totalSize = maxSize;
		memoryPtr = new char[maxSize];
		memoryIsAllocated = true;
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
