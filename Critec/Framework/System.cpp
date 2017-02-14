#include "System.h"

void MSGBOX(char* __string_,...) {
	char __str345__a[255];

	va_list a;
	va_start(a, __string_);
		//vsprintf(__str345__a, __string_, a);
		vsprintf_s(__str345__a, 255, __string_, a);
	va_end(a);

	MessageBox(NULL, __str345__a, "", MB_OK);
}


/*

*/
char* crVec3_str(crVec3 vector)  {
	char* value = new char[100];
	sprintf_s(value, 100, "%5.5f@%5.5f@%5.5f", vector.x, vector.y, vector.z);
	return (value);
}

char* int_str(int inum)  {
	char* value = new char[100];
	sprintf_s(value, 100,  "%d", inum);
	return (value);
}

char* float_str(float fnum)  {
	char* value = new char[100];
	sprintf_s(value, 100, "%5.5f", fnum);
	return (value);
}

char* double_str(double dnum)  {
	char* value = new char[100];
	sprintf_s(value, 100, "%5.5f",dnum);
	return (value);
}

char* bool_str(bool bnum)  {
	return (  (bnum)?"true":"false" );
}

float*  Vec3ArrayToFloatArray( crVec3* v, int count ) {
	//int count = sizeof(v) / sizeof(crVec3);
	float* f = new float[count*3];

	for(int i=0; i<count; i+=3) {
		f[i]   = v[i/3].x;
		f[i+1] = v[i/3].y;
		f[i+2] = v[i/3].z;
	}

	return f;
}