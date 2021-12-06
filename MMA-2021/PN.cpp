#include "stdafx.h"
#include "PN.h"
#include "LT.h"

int Preorities(char operation) {
	if (operation == LEX_LEFTTHESIS || operation == LEX_RIGHTTHESIS) {
		return 1;
	}
	if (operation == LEX_MINUS || operation == LEX_PLUS) {
		return 2;
	}
	if (operation == LEX_STAR || operation == LEX_DIRSLASH) {
		return 3;
	}
}

void PN::ConvertToPolishNotation(LT::LexTable &lexTable, IT::IdTable &idtable, int index, LT::Entry* expression)
{
	std::stack<LT::Entry> stack;

	int expressionSize = 0;
	int startPosition = index;
	short leftThesis = 0;

	for (; lexTable.table[index].lexema != LEX_SEMICOLON; index++) {
		LT::Entry lex = lexTable.table[index];
		if ((lex.lexema == LEX_ID || lex.lexema == LEX_LITERAL) && idtable.table[lex.idxTI].idtype != IT::IDTYPE::F) {
			expression[expressionSize++] = lex;
		}
		else if (lex.lexema == LEX_LEFTTHESIS) {
			stack.push(lex);
		}
		else if (lex.lexema == LEX_RIGHTTHESIS) {
			while (stack.size()) {
				if (stack.top().lexema == LEX_LEFTTHESIS) break;
				expression[expressionSize++] = stack.top();
				stack.pop();
			}
			stack.pop();
		}
		else if (lex.lexema == LEX_ID && idtable.table[lexTable.table[index].idxTI].idtype == IT::IDTYPE::F)
		{
			LT::Entry copy = lexTable.table[index];
			copy.lexema = LEX_COMMERCIAL_AT;
			copy.idxTI = lexTable.table[index].idxTI;
			++index;
			int countOfCommas = 0;
			while (lexTable.table[index].lexema != LEX_RIGHTTHESIS) {
				if (lexTable.table[index].lexema == LEX_COMMA)
				{
					++countOfCommas;
				}
				if (((lexTable.table[index].lexema != LEX_COMMA) && (lexTable.table[index].lexema == LEX_ID || lexTable.table[index].lexema == LEX_LITERAL)))
				{
					expression[expressionSize++] = lexTable.table[index];
				}
				++index;
			}
			expression[expressionSize++] = copy;
			expression[expressionSize].lexema = std::to_string(countOfCommas + 1).front();
			expression[expressionSize++].idxTI = -1;
		}
		else if (stack.empty() || stack.top().lexema == LEX_LEFTTHESIS) {
			stack.push(lex);
		}
		else
		{
			while (stack.size()) {
				if (Preorities(lexTable.table[index].lexema) > Preorities(stack.top().lexema)) break;
				expression[expressionSize++] = stack.top();
				stack.pop();
			}
			stack.push(lexTable.table[index]);
		}
	}
	while (stack.size() != 0)
	{
		expression[expressionSize++] = stack.top();
		stack.pop();
	}
	for (int i = 0, j = startPosition; i < expressionSize; ++i, ++j) {
		lexTable.table[j] = expression[i];
	}
	for (int i = 0; i < index - (startPosition + expressionSize); ++i) {
		for (int j = startPosition + expressionSize; j < lexTable.size; ++j) {
			lexTable.table[j] = lexTable.table[j + 1];
		}
		--lexTable.size;
	}
}


void PN::PolishNotation(LT::LexTable &lexTable, IT::IdTable &idTable)
{
	for (auto i = 0; i < lexTable.size; ++i) {
		if (lexTable.table[i].lexema == LEX_EQUAL || lexTable.table[i].lexema == LEX_RETURN) {
			LT::Entry expression[100];
			PN::ConvertToPolishNotation(lexTable, idTable, i + 1, expression);
		}
	}
}