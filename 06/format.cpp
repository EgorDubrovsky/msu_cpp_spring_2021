#include "format.hpp"


InvalidFormatString::InvalidFormatString(std::string mes = "NA")
{
	this->message = mes;
}

error_type StringSuitableForFormat(std::string str, size_t total_arguments, std::vector <size_t> &lb, std::vector <size_t> &rb, std::vector <size_t> &num)
{
	std::string bracket_token = "";
	int balance = 0;
	int bracket_blocks = 0;
	bracket_state state = OUT;
	size_t str_len = str.length();
	
	std::vector <bool> expected_tokens;
	for (size_t i = 0; i < total_arguments; i++)
		expected_tokens.push_back(false);
	
	for (size_t i = 0; i < str_len; i++)
	{
		//  Смотрим, что внутри скобок
		if (state == IN && str[i] != '}')
		{
			if (str[i] < '0' || str[i] > '9')
				return CONTENTS;
			bracket_token += str[i];
		}
		
		//  Обрабатываем скобки
		if (str[i] == '{')
		{
			balance++;
			state = IN;
			lb.push_back(i);
		}
		else if (str[i] == '}')
		{
			balance--;
			bracket_blocks++;
			state = OUT;
			rb.push_back(i);
			if (balance < 0)
				return BALANCE;
			if (bracket_token == "")
				return CONTENTS;
			num.push_back(std::stoi(bracket_token));
			if (std::stoul(bracket_token) >= total_arguments)
				return NUMERATION;
			else
				expected_tokens[std::stoul(bracket_token)] = true;
			bracket_token = "";
		}
	}
	if (balance != 0)
		return BALANCE;
	
	//  Проверяем нумерацию
	for (auto p = expected_tokens.begin(); p != expected_tokens.end(); p++)
		if (!(*p))
			return NUMERATION;
	
	return OK;
}