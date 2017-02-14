#include "sys.h"

bool CompareString(char* str1, char* str2) {
	unsigned int str1_l = strlen(str1);
	unsigned int str2_l = strlen(str2);
	
	if (str1_l != str2_l) return false;

	for (unsigned int i=0; i<str1_l; i++) {
		if (str1[i] == str2[i]) continue;
		return false;
	}

	return true;
}

char* TruncateString (unsigned int len, char* str ) {
	if (len>strlen(str)) 
		return '\0';

	char* Cs = new char[len];

	for (unsigned int i=0; i<len; i++) 
		Cs[i] = str[i];

	return &Cs[ 0 ];
}