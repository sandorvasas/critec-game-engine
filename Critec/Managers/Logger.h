// Copyright (C) 2007 by Sandor Vasas
//

#ifndef __CRITEC_LOGGER_H_
#define __CRITEC_LOGGER_H_

#include <stdio.h>
#include <windows.h>

class crLogger{
private:
	FILE* file;
	char* logFileName;
public:
	crLogger( void ) {};
	~crLogger( void );
	
	void	Open	( char* logFileName );
	void	Close	( void );
	void	Log		( char* __str, ... );
};


#endif