#include "vector.hpp"
#include <cassert>


void DefaultConstructorTest()
{
	Vector <char> v;
	
	assert(v.size() == 0 && v.capacity() == 0);
}

void PushBackTest()
{
	Vector <int> v;
	v.push_back(1);
	v.push_back(8);
	v.push_back(1);
	v.push_back(2);
	
	assert(v.size() == 4 && v[0] == 1 && v[1] == 8 && v[2] == 1 && v[3] == 2);
}

void PopBackTest()
{
	Vector <std::string> v;
	v.push_back("abc");
	v.push_back("def");
	v.push_back("ghi");
	v.pop_back();
	v.pop_back();
	
	assert(v.size() == 1 && v[0] == "abc");
}

void EmptyPopTest()
{
	Vector <bool> v;
	std::string message;
	try
	{
		v.pop_back();
		message = "OK";
	}
	catch(std::logic_error)
	{
		message = "Error";
	}
	assert (message == "Error");
	
	v.push_back(true);
	v.pop_back();
	assert(v.size() == 0);
	
	try
	{
		v.pop_back();
		message = "OK";
	}
	catch(std::logic_error)
	{
		message = "Error";
	}
	assert (message == "Error");
}

void IndexTest()
{
	Vector <int> v({1, 2, 3, 4, 5, 4, 3, 2, 1});
	assert(v[0] == 1 && v[2] == 3 && v[4] == 5 && v[8] == 1);
	
	v[1] = 1831;
	assert(v[1] == 1831);
}

void OutOfRangeIndexTest()
{
	Vector <std::string> v(3, "Peace is nice"); // Вектор из 3-х элементов со значениями по умолчанию
	std::string message;
	try
	{
		v[3] = "Peace is better than Chicken and Rice";
		message = "OK";
	}
	catch (std::out_of_range)
	{
		message = "Error";
	}
	assert (message == "Error");
}

void EmptyTest()
{
	Vector <std::string> v;
	assert(v.empty());
	
	v.push_back("asdf");
	assert(!v.empty());
	
	v.pop_back();
	assert(v.empty());
}

void SizeTest()
{
	Vector <char> v = {'c', 'a', 'r'};
	assert(v.size() == 3);
	
	v.emplace_back({'e', 'f', 'u', 'l'});
	assert(v.size() == 7);
	
	v.pop_back();
	v.pop_back();
	v.pop_back();
	assert(v.size() == 4);
}

void ResizeSmallerTest()
{
	Vector <std::string> v(5, "AAA");
	size_t old_capacity = v.capacity();
	v.resize(2);
	
	assert(v.size() == 2 && v.capacity() == old_capacity && v[0] == "AAA" && v[1] == "AAA");
}

void ResizeBiggerTest()
{
	Vector <int> v({3, 1, 4, 1, 5});
	v.resize(7, 64);
	
	assert(v.size() == 7 && v[5] == 64 && v[6] == 64);
}

void ReserveSmallerTest()
{
	Vector <char> v({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'});
	size_t old_size = v.size();
	size_t old_capacity = v.capacity();
	v.reserve(4);
	
	assert(v.size() == old_size && v.capacity() == old_capacity);
}

void ReserveBiggerTest()
{
	Vector <char> v({'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'});
	size_t old_size = v.size();
	size_t old_capacity = v.capacity();
	v.reserve(100);
	
	assert(v.size() == old_size && v.capacity() == 100 && v.capacity() != old_capacity);
}

void IteratorTest()
{
	Vector <std::string> v({"This ", "memorial ", "is ", "dedicated ", "to ", "those ",
							"who ", "perished ", "on ", "the ", "climb.\n"});
	std::string message = "";
	Vector<std::string>::iterator it = v.begin();
	while (it != v.end())
	{
		message += *it;
		++it;
	}
	
	assert (message == "This memorial is dedicated to those who perished on the climb.\n");
}

void ReverseIteratorTest()
{
	Vector <char> v({'e', 'g', 'a', 's', 's', 'e', 'm', ' ', 'e', 's', 'r', 'e', 'v', 'e', 'R'});
	std::string message = "";
	Vector<char>::reverse_iterator it = v.rbegin();
	while (it != v.rend())
	{
		message += *it;
		++it;
	}
	
	assert (message == "Reverse message");
}



int main()
{
	DefaultConstructorTest();
	PushBackTest();
	PopBackTest();
	EmptyPopTest();
	IndexTest();
	OutOfRangeIndexTest();
	EmptyTest();
	SizeTest();
	ResizeSmallerTest();
	ResizeBiggerTest();
	ReserveSmallerTest();
	ReserveBiggerTest();
	IteratorTest();
	ReverseIteratorTest();
	
	std::cout << "All tests passed!\n";
}