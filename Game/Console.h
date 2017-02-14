#ifndef __CONSOLE_H_
#define __CONSOLE_H_

#include "../Critec/Core.h"
#pragma hdrstop

typedef void (*CFUNC)();

struct CConsoleCmd {
	CFUNC	function;
	char*	command;
};

struct CConsoleCmds {
	int numCmdList;
	CConsoleCmd* CmdList;

	void	ProcessCommand	(char* command);
	void	AddCommand		(char* command, void* function);
};

class CConsole {
private:
	double t;
	int		deactivator;
public:
	char	currentCommand[250];
	int		numPrevCommands;
	char*	prevCommands[120];
	Text	Font;
	CConsoleCmds	Commands;
	float	color[4];

	bool	active;
	bool*	keys;

	CConsole();
	~CConsole();

	void	Activate	(bool* keys, int deactivator);
	void	Deactivate	();
	void	Render		();
	void	Listen		();
	void	Print		(char* text);
};

#endif