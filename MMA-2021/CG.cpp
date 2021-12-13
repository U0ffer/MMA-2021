#include "stdafx.h"
#include "CG.h"
#include "LT.h"
#include "IT.h"

CG::Generation::Generation(LT::LexTable lexT, IT::IdTable idT, std::string outFile)
{
	lexTable = lexT;
	idTable = idT;
	out = std::ofstream(outFile);
}

void CG::Generation::start()
{
	head();
	constants();
	data();
	code();
}

void CG::Generation::head()
{
	out << ".586\n";
	out << ".model flat, stdcall\n";
	out << "includelib libucrt.lib\n";
	out << "includelib kernel32.lib\n";
	out << "includelib ../Debug/MMA_Lib.lib\n";
	out << "ExitProcess PROTO : DWORD\n";
	out << "_compare PROTO : DWORD, :DWORD\n";
	out << "_strln PROTO : DWORD\n";
	out << "_out PROTO : DWORD\n";
	out << "_outInt PROTO : DWORD\n\n";
	out << "\n.stack 4096\n";
}

void CG::Generation::constants()
{
	out << ".const\n";
	out << "\t_DIVISION_BY_ZERO_ERROR BYTE 'Ошибка выполнения: деление на ноль', 0\n";
	out << "\t_OVERFLOW_ERROR BYTE 'Ошибка выполнения: переполнение', 0\n";
	for (int i = 0; i < idTable.size; i++)
		if (idTable.table[i].idtype == IT::IDTYPE::L)
		{
			out << "\t" << idTable.table[i].id;
			if (idTable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << " BYTE " << '\'' << idTable.table[i].value.vstr.str << '\'' << ", 0";
			if (idTable.table[i].iddatatype == IT::IDDATATYPE::UINT)
				out << " DWORD " << idTable.table[i].value.vint;
			out << '\n';
		}
}

void CG::Generation::data()
{
	out << ".data\n";
	for (int i = 0; i < idTable.size; i++)
	{
		if (idTable.table[i].idtype == IT::IDTYPE::V) {
			out << '\t';
			out << '_' << idTable.table[i].scope << idTable.table[i].id;
			out << "\t\tDWORD 0 ";
			if (idTable.table[i].iddatatype == IT::IDDATATYPE::STR)
				out << "; str\n";
			else
				out << "; int\n";
		}
	}
}

void CG::Generation::code()
{
	out << "\n.code\n";
	int indOfFunc = -1;
	int indOflex = -1;
	bool func = false;
	bool main = false;
	int blockOfCode = 0;
	int ifStatement = 0;
	int stackRet = 0;
	int Ifsn = 0;
	int flagelse = 0;
	char operation;
	for (int i = 0; i < lexTable.size; i++) {
		switch (lexTable.table[i].lexema) {
		case LEX_FUNCTION: {
			if (func || main)
				break;
			indOfFunc = i + 1;
			out << '_' << idTable.table[lexTable.table[indOfFunc].idxTI].id << " PROC ";
			func = true;
			int backup = i;
			while (lexTable.table[i].lexema != LEX_RIGHTTHESIS)
				i++;
			while (lexTable.table[i].lexema != LEX_LEFTTHESIS)
			{
				if (lexTable.table[i].lexema == LEX_ID)
				{
					stackRet += 4;
					out << '_' << idTable.table[lexTable.table[i].idxTI].id << ": DWORD";
					if (lexTable.table[i - 2].lexema != LEX_LEFTTHESIS)
						out << ", ";
				}
				i--;
			}
			i = backup;
			out << std::endl;
			break;
		}
		case LEX_MAIN: {
			main = true;
			out << "main PROC\n";
			break;
		}

		case LEX_RETURN: {
			end();
			if (main) {
				out << "\tpush\t\t";
				if (lexTable.table[i + 1].lexema == LEX_ID) {
					out << '_' << idTable.table[lexTable.table[i + 1].idxTI].scope
						<< idTable.table[lexTable.table[i + 1].idxTI].id;
				}
				else
					out << idTable.table[lexTable.table[i + 1].idxTI].id;
				out << std::endl;
			}
			else
			{
				if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::STR) {
					if (idTable.table[lexTable.table[i + 1].idxTI].idtype != IT::IDTYPE::L)
						out << "\tmov\t\teax, " << '_' << idTable.table[lexTable.table[i + 1].idxTI].scope
						<< idTable.table[lexTable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
					else
						out << "\tmov\t\teax, offset " << idTable.table[lexTable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
				}
				else {
					if (idTable.table[lexTable.table[i + 1].idxTI].idtype == IT::IDTYPE::L)
						out << "\tmov\t\teax, " << idTable.table[lexTable.table[i + 1].idxTI].id
						<< "\n\tret\t\t" << stackRet << std::endl;
					else
						out << "\tmov\t\teax, " << '_' << idTable.table[lexTable.table[i + 1].idxTI].scope
						<< idTable.table[lexTable.table[i + 1].idxTI].id << "\n\tret\t\t" << stackRet << std::endl;
				}
				stackRet = 0;
			}
			break;
		}
		case LEX_PRINT: {
			if (lexTable.table[i + 1].lexema == LEX_ID) {
				if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::UINT) {
					out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i + 1].idxTI].scope
						<< idTable.table[lexTable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_outInt\n\n";
				}
				else {
					out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i + 1].idxTI].scope
						<< idTable.table[lexTable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_out\n\n";
				}
			}
			else if (lexTable.table[i + 1].lexema == LEX_LITERAL) {
				if (idTable.table[lexTable.table[i + 1].idxTI].iddatatype == IT::IDDATATYPE::UINT) {
					out << "\tpush\t\t" << idTable.table[lexTable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_outInt\n\n";
				}
				else {
					out << "\tpush\t\toffset " << idTable.table[lexTable.table[i + 1].idxTI].id;
					out << "\n\tcall\t\t_out\n\n";
				}
			}
			break;
		}
		case LEX_EQUAL: {
			indOflex = i - 1;	
			while (lexTable.table[i].lexema != LEX_SEMICOLON) {
				if (lexTable.table[i].lexema == LEX_ID) {	
					if (idTable.table[lexTable.table[i].idxTI].idtype != IT::IDTYPE::F)
					{
						if (idTable.table[lexTable.table[i].idxTI].idtype == IT::IDTYPE::P)
						{
							out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i].idxTI].id << "\n";
						}
						else
							out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i].idxTI].scope
								<< idTable.table[lexTable.table[i].idxTI].id << "\n";
					}
				}
				if (lexTable.table[i].lexema == LEX_LITERAL) {
					if (idTable.table[lexTable.table[i].idxTI].iddatatype == IT::IDDATATYPE::UINT)
						out << "\tpush\t\t";
					else
						out << "\tpush\t\toffset ";
					out << idTable.table[lexTable.table[i].idxTI].id << "\n";
				}
				if (lexTable.table[i].lexema == LEX_COMMERCIAL_AT)
				{
					out << "\tcall\t\t" << '_' << idTable.table[lexTable.table[i].idxTI].id << "\n";
					out << "\tpush\t\teax\n";
				}
				if (lexTable.table[i].lexema == LEX_PLUS)
				{
					out << "\n";
					out << "\tpop\t\teax\n";
					out << "\tpop\t\tebx\n";
					out << "\tadd\t\teax, ebx\n";
					out << "\tjo\t\tEXIT_OVERFLOW\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lexTable.table[i].lexema == LEX_MINUS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tsub\t\teax, ebx\n";
					out << "\tjo\t\tEXIT_OVERFLOW\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lexTable.table[i].lexema == LEX_STAR)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\timul\t\teax, ebx\n";
					out << "\tjo\t\tEXIT_OVERFLOW\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lexTable.table[i].lexema == LEX_DIRSLASH)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\ttest\t\tebx, ebx\n";
					out << "\tjz\t\tEXIT_DIV_ON_NULL\n";
					out << "\tcdq\n";
					out << "\tidiv\t\tebx\n";
					out << "\tjo\t\tEXIT_OVERFLOW\n";
					out << "\tpush\t\teax\n";
					out << "\n";
				}
				if (lexTable.table[i].lexema == LEX_MORE)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tja\t\tMORE" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjb\t\tLESS" << lexTable.table[i].sn << "\n";
					out << "MORE" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "LESS" << lexTable.table[i].sn << ":";
					out << "\n";
				}

				if (lexTable.table[i].lexema == LEX_LESS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjb\t\tLESS" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tja\t\tMORE" << lexTable.table[i].sn << "\n";
					out << "LESS" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "MORE" << lexTable.table[i].sn << ":";
					out << "\n";
				}

				if (lexTable.table[i].lexema == LEX_FULL_EQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjne\t\tNOTEQUAL" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tje\t\tEQUAL" << lexTable.table[i].sn << "\n";
					out << "EQUAL" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "NOTEQUAL" << lexTable.table[i].sn << ":";
					out << "\n";
				}

				if (lexTable.table[i].lexema == LEX_NOT_FULL_EQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjne\t\tNOTEQUAL" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tje\t\tEQUAL" << lexTable.table[i].sn << "\n";
					out << "NOTEQUAL" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "EQUAL" << lexTable.table[i].sn << ":";
					out << "\n";
				}

				if (lexTable.table[i].lexema == LEX_MORE_OR_EQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjae\t\tMOREOREQUAL" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjnb\t\tLESS" << lexTable.table[i].sn << "\n";
					out << "MOREOREQUAL" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "LESS" << lexTable.table[i].sn << ":";
					out << "\n";
				}

				if (lexTable.table[i].lexema == LEX_LESS_OR_EQUALS)
				{
					out << "\n";
					out << "\tpop\t\tebx\n";
					out << "\tpop\t\teax\n";
					out << "\tcmp\t\teax, ebx\n";
					out << "\tjbe\t\tLESSOREQUALS" << lexTable.table[i].sn << "\n";
					out << "\tpush\t\t0\n";
					out << "\tjna\t\tMORE" << lexTable.table[i].sn << "\n";
					out << "LESSOREQUALS" << lexTable.table[i].sn << ":" << "\n";
					out << "\tpush\t\t1\n";
					out << "MORE" << lexTable.table[i].sn << ":";
					out << "\n";
				}
				i++;
			}
			out << "\tpop\t\t\t" << '_' << idTable.table[lexTable.table[indOflex].idxTI].scope
				<< idTable.table[lexTable.table[indOflex].idxTI].id << "\n\n";
			break;
		}
		case LEX_IF: {
			flagelse = 0;
			++ifStatement;
			operation = ' ';
			if (lexTable.table[i + 2].lexema != LEX_LITERAL)
				out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i+2].idxTI].scope << idTable.table[lexTable.table[i + 2].idxTI].id << "\n";
			else
				out << "\tpush\t\t" << idTable.table[lexTable.table[i + 2].idxTI].id << "\n";

			if (lexTable.table[i + 4].lexema != LEX_LITERAL)
				out << "\tpush\t\t" << '_' << idTable.table[lexTable.table[i+2].idxTI].scope << idTable.table[lexTable.table[i + 4].idxTI].id << "\n";
			else
				out << "\tpush\t\t" << idTable.table[lexTable.table[i + 4].idxTI].id << "\n";

			out << "\tpop\t\tebx\n";
			out << "\tpop\t\teax\n";
			out << "\tcmp\t\teax, ebx\n";
			Ifsn = lexTable.table[i].sn;
			int j = i;
			int countOfMrequals = 0;
			while (lexTable.table[j].lexema != LEX_LSEQUAL || countOfMrequals != 0) {
				if (lexTable.table[j].lexema == LEX_MREQUAL) ++countOfMrequals;
				else if (lexTable.table[j + 1].lexema == LEX_LSEQUAL) --countOfMrequals;
				j++;
			}	
			if (lexTable.table[j + 1].lexema == LEX_ELSE)
				flagelse = 1;
			switch (lexTable.table[i + 3].lexema) {

			case LEX_FULL_EQUALS:
			{
				out << "\tjne\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tje\t\tTRUE" << Ifsn << "\n";
					operation = LEX_FULL_EQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_NOT_FULL_EQUALS:
			{
				out << "\tje\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjne\t\tTRUE" << Ifsn << "\n";
					operation = LEX_EQUAL;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_MORE:
			{
				out << "\tjna\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjnb\t\tTRUE" << Ifsn << "\n";
					operation = LEX_MORE;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_LESS:
			{
				out << "\tjnb\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjna\t\tTRUE" << Ifsn << "\n";
					operation = LEX_LESS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_MORE_OR_EQUALS:
			{
				out << "\tjb\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tja\t\tTRUE" << Ifsn << "\n";
					operation = LEX_MORE_OR_EQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}

			case LEX_LESS_OR_EQUALS:
			{
				out << "\tja\t\tFALSE" << Ifsn << "\n";
				if (flagelse == 1) {
					out << "\tjb\t\tTRUE" << Ifsn << "\n";
					operation = LEX_LESS_OR_EQUALS;
					out << "TRUE" << Ifsn << ": " << "\n";
				}
				break;
			}
			default:break;
			}
			break;
		}
		case LEX_MREQUAL:
			if (lexTable.table[i - 1].lexema == LEX_SEMICOLON || lexTable.table[i - 1].lexema == LEX_LSEQUAL)
				++blockOfCode;
			break;
		case LEX_LSEQUAL: {
			if (blockOfCode > 0)
			{
				--blockOfCode;
			}
			else if (ifStatement > 0)
			{
				if (flagelse == 1 && lexTable.table[i + 1].lexema == LEX_ELSE) {
					out << "\tjmp\t\tIFOUT" << Ifsn << "\n";
					out << "FALSE" << Ifsn << ": " << "\n";
					++ifStatement;
				}
				else if (flagelse == 0 && lexTable.table[i + 1].lexema != LEX_ELSE) {
					out << "FALSE" << Ifsn << ": " << "\n";
				}
				else if (flagelse == 1)
					out << "IFOUT" << Ifsn << ": " << "\n";
				--ifStatement;
			}
			else if (func)
			{
				out << '_' << idTable.table[lexTable.table[indOfFunc].idxTI].id << " ENDP\n\n";
				func = false; 
				indOfFunc = 0;
			}
			else
			{
				out << "\tcall\t\tExitProcess\n\nmain ENDP\n";
			}
			
			break;
		}
		
		default:break;
		}
	}
	out << "end main\n";
}

void CG::Generation::end()
{
	out << "\n\n\tjmp EXIT\nEXIT_DIV_ON_NULL:\n\tpush offset _DIVISION_BY_ZERO_ERROR\n\tcall _out\n\tpush -1\n\tcall ExitProcess";
	out << "\n\nEXIT_OVERFLOW:\n\tpush offset _OVERFLOW_ERROR\n\tcall _out\n\tpush -2\n\tcall ExitProcess";
	out << "\n\nEXIT:\n";
}