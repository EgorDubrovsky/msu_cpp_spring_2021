#pragma once

#include <string>
#include <functional>
#include <iostream>

enum ParserState
{
	EMPTY,
	DIGIT,
	STRING
};

const uint64_t MAX_DIGIT = 18446744073709551615ULL;

class TokenParser
{
	std::function<std::string(const std::string &)> start_func = nullptr;
	std::function<std::string(const std::string &)> end_func = nullptr;
	std::function<std::string(const std::string &)> digit_token_func = nullptr;
	std::function<std::string(const std::string &)> str_token_func = nullptr;
	
	ParserState state = EMPTY;
	std::string cur_token = "";
	uint64_t total_digits = 0;
	uint64_t total_strings = 0;

public:
    TokenParser() = default;

    // Устанавливаем callback-функцию перед стартом парсинга
    void SetStartCallback(std::function<std::string(const std::string &)>);

    // Устанавливаем callback-функцию после окончания парсинга
    void SetEndCallback(std::function<std::string(const std::string &)>);

    // Устанавливаем callback-функцию для обработки чисел
    void SetDigitTokenCallback(std::function<std::string(const std::string &)>);
	
	// Устанавливаем callback-функцию для обработки строк
	void SetStringTokenCallback(std::function<std::string(const std::string &)>);

    // Парсим строку
    std::string Parse(const std::string &);
	
	//  Доступ к параметрам подсчёта токенов
	uint64_t GetTotalDigitTokens();
	uint64_t GetTotalStringTokens();
};