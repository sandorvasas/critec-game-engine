#include "Logger.h"


void crLogger::Open( char* logFileName ) {
	this->logFileName = logFileName;
	fopen_s(&file, logFileName, "w");
	fclose(file);
}

void crLogger::Close( void ) {
//	fclose(file);
}

crLogger::~crLogger() {
	Close();
}

void crLogger::Log( char *__str, ... ) {
	va_list a;
	char	txt[1500];
	
	va_start(a, __str);
		vsprintf_s(txt, 1500, __str, a);
	va_end(a);

	fopen_s(&file, logFileName, "a+");
	fprintf(file, txt);
	fclose(file);
}
