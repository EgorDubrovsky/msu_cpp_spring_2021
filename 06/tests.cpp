#include "format.hpp"
#include <cassert>

//  Тест на бросание исключения при неправильном балансе скобок
void BracketBalanceTest()
{
	std::string message;
	try
	{
		format_str("{0}{", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad bracket balance\n");
	
	try
	{
		format_str("abc }{0}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad bracket balance\n");
}

//  Тест на бросание исключения при неправильном содержании скобок (что-то кроме натуральных чисел)
void BracketContentsTest()
{
	std::string message;
	try
	{
		format_str("hello {0.5}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Expected unsigned integer in brackets\n");
	
	try
	{
		format_str("hello {a}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Expected unsigned integer in brackets\n");
	
	try
	{
		format_str("hello {{0}}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Expected unsigned integer in brackets\n");
	
	try
	{
		format_str("hello {-0}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Expected unsigned integer in brackets\n");
}

//  Тест на бросание исключения при неправильной нумерации внутри скобок
void NumerationTest()
{
	std::string message;
	try
	{
		format_str("hello {3}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad numeration for formatting parameters\n");
	
	try
	{
		format_str("hello {0}", 2, 3);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad numeration for formatting parameters\n");
	
	try
	{
		format_str("hello {0}{1}", 2);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad numeration for formatting parameters\n");
	
	try
	{
		format_str("hello {0}{2}{0}", 1, 2, 3);
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad numeration for formatting parameters\n");
}

//  Тест на замену всей строчки
void FullReplacementTest()
{
	auto text = format_str("{0}", 2);
	assert(text == "2");
	
	text = format_str("{0}{2}{1}", '@', ".com", "gmail");
	assert(text == "@gmail.com");
}

//  Тест для вызова функции без параметров форматирования
void NoParametersTest()
{
	auto text = format_str("asd");
	assert(text == "asd");
	
	std::string message;
	try
	{
		format_str("hello {0}");
		message = "OK";
	}
	catch(InvalidFormatString &err)
	{
		message = err.message;
	}
	assert (message == "ERROR: Bad numeration for formatting parameters\n");
}

//  Тест на индексы из нескольких цифр
void DoubleDigitTest()
{
	auto text = format_str("{0} {1} {2} {3} {4} {5} {6} {7} {8} {9} {10}", 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);
	assert(text == "10 9 8 7 6 5 4 3 2 1 0");
}

//  Тест на вывод в поток
void OstreamTest()
{
	std::ostringstream stream;
    stream << format_str("{1}+{1} = {0}", 2, "one");
	assert(stream.str() == "one+one = 2");
}

//  Общий тест на работоспособность функции
void GeneralTest()
{
	auto text = format_str("{0} and {1} are {2}", 2.5, -0.33, "rational values");
	assert(text == "2.5 and -0.33 are rational values");
	
	text = format_str("1{4}34{3}6{2}{1}9{0}", "cake", '8', 3 + 4, 5, format_str("{0}", 2));
	assert(text == "123456789cake");
	
	text = format_str("{0} / {1} = {2}", 3, 0, "INF");
	assert(text == "3 / 0 = INF");
}

int main()
{
	BracketBalanceTest();
	BracketContentsTest();
	NumerationTest();
	FullReplacementTest();
	NoParametersTest();
	DoubleDigitTest();
	OstreamTest();
	GeneralTest();
	
	std::cout << "All tests passed!\n";
}