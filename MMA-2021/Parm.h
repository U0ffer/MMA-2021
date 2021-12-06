#pragma once

#define PARM_IN "-in:"
#define PARM_OUT "-out:"
#define PARM_LOG "-log:"
#define PARM_MAX_SIZE 300
#define PARM_OUT_DEFAULT_EXT ".out"
#define PARM_LOG_DEFAULT_EXT ".log"


namespace Parm
{
	struct PARM
	{
		std::string in = "";
		std::string out = "";
		std::string log = "";
	};

	PARM getParm(int argc, char* argv[]);
}