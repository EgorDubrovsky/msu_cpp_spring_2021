#include "callback_functions.hpp"

std::string HelloWorld(const std::string &param)
{
	return("Hello, world!\n");
}

std::string AppendVariableName(const std::string &param)
{
	return("x = ");
}

std::string GoodbyeWorld(const std::string &param)
{
	return("Goodbye, world!\n");
}

std::string FoundNumber(const std::string &param)
{
	return("Found a number: " + param + "\n");
}

std::string Increase(const std::string &param)
{
	return(std::to_string(stoi(param) + 1));
}

std::string FoundString(const std::string &param)
{
	return("Found a string: " + param + "\n");
}