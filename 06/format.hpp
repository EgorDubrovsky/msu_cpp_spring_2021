#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

enum bracket_state 
{
	IN, 
	OUT
};

enum error_type 
{
	OK, 
	BALANCE,      //  Ошибка баланса скобок
	CONTENTS,     //  Скобки содержат что-то кроме натуральных чисел
	NUMERATION    //  Ошибка нумерации для форматирования
};

class InvalidFormatString
{
public:
	std::string message = "NA";
	InvalidFormatString(std::string);
};

//  Проверка на пригодность для форматирования
error_type StringSuitableForFormat(std::string, size_t, std::vector <size_t> &, std::vector <size_t> &, std::vector <size_t> &);

//  Построение вектора аргументов
inline std::vector <std::string> return_args_vector()
{
	std::vector <std::string> out;
	return out;
}

template <class T, class... Args>
inline std::vector <std::string> return_args_vector(const T& arg, Args&&... args)
{
	std::vector <std::string> out;
	std::ostringstream arg_str;
    arg_str << arg;
	out.push_back(arg_str.str());
	
	std::vector others = return_args_vector(args...);
	out.insert(std::end(out), std::begin(others), std::end(others));
    return out;
}


//  Функция форматирования
template <class... Args>
std::string format_str(const std::string &to_format, Args&&... args)
{
	std::string to_return = to_format;
	
	//  Получаем вектор аргументов
	std::vector <std::string> arg_vec = return_args_vector(args...);
	size_t total_arguments = arg_vec.size();
	
	//  Проверяем формат строки. Если что-то не так - кидаем исключение
	std::vector <size_t> left_brackets;
	std::vector <size_t> right_brackets;
	std::vector <size_t> numbers;
	error_type check_format = StringSuitableForFormat(to_format, total_arguments, left_brackets, right_brackets, numbers);
	switch(check_format)
	{
		case BALANCE:
			throw InvalidFormatString("ERROR: Bad bracket balance\n");
		case CONTENTS:
			throw InvalidFormatString("ERROR: Expected unsigned integer in brackets\n");
		case NUMERATION:
			throw InvalidFormatString("ERROR: Bad numeration for formatting parameters\n");
		case OK:
			break;
	}
	
	//  Преобразуем строку
	size_t offset = 0;
	size_t brackets = left_brackets.size();
	for (size_t i = 0; i < brackets; i++)
	{
		to_return.replace(left_brackets[i] + offset, right_brackets[i] - left_brackets[i] + 1, arg_vec[numbers[i]]);
		offset += arg_vec[numbers[i]].length() - (right_brackets[i] - left_brackets[i]) - 1;
	}
	
	return to_return;
}
