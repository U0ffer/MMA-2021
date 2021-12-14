#include "stdafx.h"
#include "Error.h"
#include "Parm.h"
#include "In.h"
#include "Log.h"
#include "IT.h"
#include "LT.h"
#include "Lex.h"
#include "GRB.h"
#include "MFST.h"
#include "PN.h"
#include "Sem.h"
#include "CG.h"

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getParm(argc, argv);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		In::IN in = In::getin(parm.in);
		Log::WriteIn(log, in);
		IT::IdTable idTable = IT::Create(in.size);
		LT::LexTable lexTable = LT::Create(in.size);
		Lex::Scan(lexTable, idTable, in, parm, log);
		MFST::Mfst mfst(lexTable, GRB::getGreibach(), parm.mfst);
		mfst.start(*log.stream);
		Log::WriteLine(log, "------ Синтаксический анализ выполнен без ошибок ------", "");
		mfst.savededucation();
		mfst.printrules();
		Sem::checkSemantic(lexTable, idTable);
		Log::WriteLine(log, "------ Семантический анализ выполнен без ошибок ------", "");
		PN::PolishNotation(lexTable, idTable);
		Log::WriteLine(log, "------ Польская нотация выполнена без ошибок ------", "");
		CG::Generation writeToOut = CG::Generation(lexTable, idTable, parm.out);
		writeToOut.start();
		Log::WriteLine(log, "------ Генерация кода выполнен без ошибок ------", "");
		#ifdef _DEBUG
			Log::WriteLine(log, "------ Таблица идентификаторов ------", "");
			IT::ShowTable(idTable, log.stream);
			Log::WriteLine(log, "------ Таблица лексем ------", "");
			LT::ShowTable(lexTable, log.stream);
			CG::Generation writeToASM = CG::Generation(lexTable, idTable, "../MMA-ASM/asm.asm");
			writeToASM.start();
		#endif 
		#ifndef _DEBUG
			system("compile.bat");
		#endif
		Log::Close(log);
	}
	catch (Error::ERROR err)
	{
		Log::WriteError(log, err);
		Log::Close(log);
	}
	system("pause");
	return 0;
}