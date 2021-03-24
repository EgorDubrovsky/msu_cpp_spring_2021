#include <iostream>
#include "sphere01.hpp"

//  Корректность учёта суммарной и использованной памяти
void UsedMemoryTest()
{
	Allocator allocator;
	allocator.makeAllocator(100);
	allocator.alloc(20);
	if (allocator.getTotalSize() == 100 && allocator.getUsedSize() == 20)
		std::cout << "Used Memory Test: OK\n";
	else
		std::cerr << "Used Memory Test: fail\n";
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
	if (allocator.getTotalSize() == 100 && allocator.getUsedSize() == 0 &&
	mem_ptr1 == mem_ptr2)
		std::cout << "Reset Test: OK\n";
	else
		std::cerr << "Reset Test: fail\n";
}

//  Проверка метода alloc: выдача nullptr при нехватке памяти
void AllocNullptrTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(10);
	char_ptr = allocator.alloc(20);
	if (char_ptr == nullptr)
		std::cout << "Alloc Nullptr Test: OK\n";
	else
		std::cerr << "Alloc Nullptr Test: fail\n";
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
	if (char_ptr == nullptr && allocator.getUsedSize() == 60)
		std::cout << "Multiple Alloc Nullptr Test: OK\n";
	else
		std::cerr << "Multiple Alloc Test: fail\n";
}

//  Корректность работы метода alloc
void SingleAllocTest()
{
	Allocator allocator;
	char *char_ptr;
	allocator.makeAllocator(100);
	char_ptr = allocator.alloc(20);
	char_ptr[0] = 'a';
	if (allocator.getMemoryPtr()[0] == 'a' && allocator.getUsedSize() == 20)
		std::cout << "Single Alloc Test: OK\n";
	else
		std::cerr << "Single Alloc Test: fail\n";
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
	if (allocator.getMemoryPtr()[20] == 'a' && allocator.getUsedSize() == 60)
		std::cout << "Multiple Alloc Test: OK\n";
	else
		std::cerr << "Multiple Alloc Test: fail\n";
}

//  Корректность работы метода makeAllocator при последовательных вызовах
void MultipleMakeTest()
{
	Allocator allocator;
	allocator.makeAllocator(100);
	allocator.alloc(20);
	allocator.makeAllocator(150);
	if (allocator.getTotalSize() == 150 && allocator.getUsedSize() == 0)
		std::cout << "Multiple Make Test: OK\n";
	else
		std::cerr << "Multiple Make Test: fail\n";
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
}