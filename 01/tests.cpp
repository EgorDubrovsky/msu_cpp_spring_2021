#include <iostream>
#include <cassert>
#include "allocator.hpp"

//  Корректность учёта суммарной и использованной памяти
void UsedMemoryTest()
{
	Allocator allocator;
	allocator.makeAllocator(100);
	allocator.alloc(20);
	assert (allocator.getTotalSize() == 100 && allocator.getUsedSize() == 20);

}

//  Корректность работы метода reset
void ResetTest()
{
	Allocator allocator;
	char *mem_ptr1, *mem_ptr2;
	allocator.makeAllocator(100);
	mem_ptr1 = allocator.getMemoryPtr();
	allocator.alloc(20);
	allocator.reset();
	mem_ptr2 = allocator.getMemoryPtr();
	assert (allocator.getTotalSize() == 100 && allocator.getUsedSize() == 0 &&
	mem_ptr1 == mem_ptr2);
}

//  Проверка метода alloc: выдача nullptr при нехватке памяти
void AllocNullptrTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(10);
	char_ptr = allocator.alloc(20);
	assert (char_ptr == nullptr);
}

//  Проверка последовательных вызовов alloc: выдача nullptr при нехватке памяти
void MultipleAllocNullptrTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(100);
	allocator.alloc(40);
	allocator.alloc(20);
	char_ptr = allocator.alloc(80);
	assert (char_ptr == nullptr && allocator.getUsedSize() == 60);
}

//  Корректность работы метода alloc
void SingleAllocTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(100);
	char_ptr = allocator.alloc(20);
	char_ptr[0] = 'a';
	assert (allocator.getMemoryPtr()[0] == 'a' && allocator.getUsedSize() == 20);
}

//  Корректность работы метода alloc при последовательных вызовах
void MultipleAllocTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(100);
	allocator.alloc(20);
	char_ptr = allocator.alloc(40);
	char_ptr[0] = 'a';
	assert (allocator.getMemoryPtr()[20] == 'a' && allocator.getUsedSize() == 60);
}

//  Корректность работы метода makeAllocator при последовательных вызовах
void MultipleMakeTest()
{
	Allocator allocator;
	allocator.makeAllocator(100);
	allocator.alloc(20);
	allocator.makeAllocator(150);
	assert (allocator.getTotalSize() == 150 && allocator.getUsedSize() == 0);
}


int main()
{
	UsedMemoryTest();
	ResetTest();
	AllocNullptrTest();
	MultipleAllocNullptrTest();
	SingleAllocTest();
	MultipleAllocTest();
	MultipleMakeTest();
	
	std::cout << "All tests passed!\n";
}