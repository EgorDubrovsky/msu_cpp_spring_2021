#include "parser.hpp"

void TokenParser::SetStartCallback(std::function<std::string(const std::string &)> func)
{
	start_func = func;
}

void TokenParser::SetEndCallback(std::function<std::string(const std::string &)> func)
{
	end_func = func;
}

void TokenParser::SetDigitTokenCallback(std::function<std::string(const std::string &)> func)
{
	digit_token_func = func;
}

void TokenParser::SetStringTokenCallback(std::function<std::string(const std::string &)> func)
{
	str_token_func = func;
}

std::string TokenParser::Parse(const std::string &input_str)
{
	std::string parsing_result = "";
	
	//  Вызываем функцию перед парсингом
	if (start_func != nullptr)
		parsing_result.append(start_func(input_str));
	
	//  Собственно парсинг
	std::string::const_iterator parse_iterator = input_str.begin();
	char cur_char;
	
	while (parse_iterator != input_str.end())
	{
		cur_char = *parse_iterator;
		//  Нашли символ пробела/табуляции/перевода строки
		if (cur_char == ' ' || cur_char == '\t' || cur_char == '\n')
			switch(state)
				{
					case EMPTY:
					break;
					case DIGIT:
						if (digit_token_func != nullptr)
							parsing_result.append(digit_token_func(cur_token));
						total_digits++;
						cur_token = "";
						state = EMPTY;
					break;
					case STRING:
						if (str_token_func != nullptr)
							parsing_result.append(str_token_func(cur_token));
						total_strings++;
						cur_token = "";
						state = EMPTY;
					break;
				}
		//  Нашли цифру
		else if (cur_char >= '0' && cur_char <= '9')
			switch(state)
			{
				case EMPTY:
					cur_token.push_back(cur_char);
					state = DIGIT;
				break;
				case DIGIT:
					cur_token.push_back(cur_char);
				break;
				case STRING:
					cur_token.push_back(cur_char);
				break;
			}
		//  Нашли другой символ
		else
			switch(state)
				{
					case EMPTY:
						cur_token.push_back(cur_char);
						state = STRING;
					break;
					case DIGIT:
						cur_token.push_back(cur_char);
						state = STRING;
					break;
					case STRING:
						cur_token.push_back(cur_char);
					break;
				}
		parse_iterator++;
	}
	
	//  Если после главного цикла остался необработанный токен:
	if (state == DIGIT && digit_token_func != nullptr)
		digit_token_func(cur_token);
	else if (state == STRING && str_token_func != nullptr)
		str_token_func(cur_token);
	
	//  Вызываем функцию после парсинга
	if (end_func != nullptr)
		parsing_result.append(end_func(input_str));
	return parsing_result;
}

uint64_t TokenParser::GetTotalDigitTokens()
{
	return total_digits;
}

uint64_t TokenParser::GetTotalStringTokens()
{
	return total_strings;
}