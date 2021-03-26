#include <iostream>
#include <cstdlib>

class Allocator
{
	size_t totalSize;
	size_t usedSize;
	char *memoryPtr;
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

