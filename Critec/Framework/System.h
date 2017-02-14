//  Copyright (C) 2007 by Sandor Vasas
//

#ifndef __CRITEC_SYSTEM_H_
#define __CRITEC_SYSTEM_H_

#include <stdio.h>
#include <windows.h>
#include "../math/vector.h"

#define C4_LIGHTBLUE			0.5f, 0.5f, 0.8f, 1.0f

void				MSGBOX( char* __string_,...);


char*				crVec3_str( crVec3 vector );
char*				int_str( int inum );
char*				float_str( float fnum );
char*				double_str( double dnum );
char*				bool_str( bool bnum );

float*				Vec3ArrayToFloatArray( crVec3* v, int count );

#endif /* __CRITEC_SYSTEM_H_ */