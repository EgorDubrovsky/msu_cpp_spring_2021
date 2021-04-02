#include <cassert>
#include "parser.hpp"
#include "callback_functions.hpp"

//  Функция чтения строки из файла
std::string ReadStringFromFile(const char *path)
{
	FILE *f = fopen(path,"r");
	std::string output_str = "";
	char file_chr;
	while ((file_chr = fgetc(f)) != EOF) 
		output_str.push_back(file_chr);
	fclose(f);
	return output_str;
}

//  Проверка парсера без установленных функций
void NoCallbacksTest()
{
	TokenParser my_parser;
	
	std::string string_to_parse = ReadStringFromFile("test1.txt");
	std::string string_parsed = my_parser.Parse(string_to_parse);
	
	assert(string_parsed == "" && my_parser.GetTotalDigitTokens() == 3 &&
	my_parser.GetTotalStringTokens() == 10);
}

//  Проверка парсера с установленными функциями
void StandardCallbacksTest()
{
	TokenParser my_parser;
	my_parser.SetStartCallback(HelloWorld);
	my_parser.SetEndCallback(GoodbyeWorld);
	my_parser.SetDigitTokenCallback(FoundNumber);
	my_parser.SetStringTokenCallback(FoundString);
	
	std::string string_to_parse = ReadStringFromFile("test1.txt");
	std::string string_parsed = my_parser.Parse(string_to_parse);
	std::string expected_parsing = "Hello, world!\n"
								   "Found a string: I\n"
								   "Found a string: was\n"
								   "Found a string: born\n"
								   "Found a string: on\n"
								   "Found a string: the\n"
								   "Found a string: 1st\n"
								   "Found a string: of\n"
								   "Found a string: January\n"
								   "Found a number: 2001\n"
								   "Found a string: At\n"
								   "Found a number: 12\n"
								   "Found a string: :\n"
								   "Found a number: 00\n"
								   "Goodbye, world!\n";
	
	assert(string_parsed == expected_parsing);
}

//  Проверка парсера с частично установленными функциями
void PartialCallbacksTest()
{
	std::string string_to_parse = ReadStringFromFile("test2.txt");
	
	TokenParser my_parser;
	my_parser.SetStartCallback(AppendVariableName);
	my_parser.SetDigitTokenCallback(Increase);
	
	std::string string_parsed = my_parser.Parse(string_to_parse);
	
	assert(string_parsed == "x = 112107");
}

//  Проверка переустановки функции парсера
void RedefineCallbackTest()
{
	std::string string_to_parse = ReadStringFromFile("test2.txt");
	
	TokenParser my_parser;
	my_parser.SetStartCallback(HelloWorld);
	my_parser.SetStartCallback(AppendVariableName);
	
	std::string string_parsed = my_parser.Parse(string_to_parse);
	
	assert(string_parsed == "x = ");
}

//  Проверка переполнения uint64_t
void Uint64OverflowTest()
{
	std::string string_to_parse = ReadStringFromFile("test3.txt");
	
	TokenParser my_parser;
	my_parser.SetDigitTokenCallback(FoundNumber);
	my_parser.SetStringTokenCallback(FoundString);
	
	std::string string_parsed = my_parser.Parse(string_to_parse);
	
	assert(string_parsed == "Found a number: 18446744073709551615\n"
							"Found a string: 18446744073709551616\n"
							"Found a string: 111111111111111111111111111111111111111111111\n");
}

int main()
{
	NoCallbacksTest();
	StandardCallbacksTest();
	PartialCallbacksTest();
	RedefineCallbackTest();
	Uint64OverflowTest();
	
	std::cout << "All tests passed!\n";
}