#pragma once
#include <unordered_map>

#include "Token.h"

enum class Operation
{
	ADD,
	SUB,
	MUL,
	DIV
};

Operation ConvertOperationCharacterToEnum(char operation_character);

class Converter
{
public:
	explicit Converter(std::unordered_map<Operation, size_t> priorities = { {Operation::ADD, 0},
																			{Operation::SUB, 0},
																			{Operation::MUL, 1},
																			{Operation::DIV, 1} });
	std::string convertToString(const std::string& expr);
	std::vector<Token> convertToTokenSequence(const std::string& expr);
private:
	std::unordered_map<Operation, size_t> priorities_;
};

