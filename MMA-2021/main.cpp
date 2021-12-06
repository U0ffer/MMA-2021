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
		Log::WriteLine(log, "------ Таблица идентификаторов ------", "");
		IT::ShowTable(idTable, log.stream);
		Log::WriteLine(log, "------ Таблица лексем ------", "");
		LT::ShowTable(lexTable, log.stream);
		MFST::Mfst mfst(lexTable, GRB::getGreibach());
		MFST_TRACE_START
		mfst.start();
		mfst.savededucation();
		mfst.printrules();
		PN::PolishNotation(lexTable, idTable);
		Log::WriteLine(log, "------ Таблица лексем после польской нотации ------", "");
		LT::ShowTable(lexTable, log.stream);
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