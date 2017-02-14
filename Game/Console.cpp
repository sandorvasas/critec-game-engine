#include "console.h"

//****************************
//   CConsoleCmds struct
//****************************
void CConsoleCmds::AddCommand(char* command, void* function) {
	CmdList = (CConsoleCmd*) realloc(&CmdList, sizeof(CConsoleCmd)*(numCmdList+1));
	CmdList[numCmdList].command  = command;
	CmdList[numCmdList].function = (CFUNC)function;
	
	numCmdList++;
}

void CConsoleCmds::ProcessCommand(char* command) {
	for (int i=0; i<numCmdList; i++) 
		if (CmdList[i].command == command)
			CmdList[i].function();
}


//****************************
//   CConsole class
//****************************
CConsole::CConsole() {
	active = false;
	keys = NULL;
	numPrevCommands = 0;
	Font.build("Tahoma", 10);
	color[0] = (float) 1;	color[1] = (float) 1;	
	color[2] = (float) 1;	color[3] = (float) 1;
}

CConsole::~CConsole() {
	if(numPrevCommands) free(prevCommands);
}

void CConsole::Activate(bool* keys, int deactivator) {
	active = true;
	this->keys   = keys;
	this->deactivator = deactivator;
	t = 0;
}

void CConsole::Deactivate() {
	active = false;
	keys = NULL;
}

void CConsole::Listen() {
	if (keys[VK_RETURN]) {
		keys[VK_RETURN] = false;
	}
	if (keys[deactivator]) Deactivate();
}

void CConsole::Render() {
	if(!active) return;

	Listen();

//	renderDevice->SetOrtho();

	glColor4d(0.7, 0.7, 0.2, 1.0);
	glBegin(GL_QUADS);
	 glVertex3d(-1, 1,   0);
	 glVertex3d( 1, 1,   0);
	 glVertex3d( 1, 1-t, 0);
	 glVertex3d(-1, 1-t, 0);
	glEnd();

	if (t<1) t += 0.005;

//	renderDevice->SetOrtho(false);
}

