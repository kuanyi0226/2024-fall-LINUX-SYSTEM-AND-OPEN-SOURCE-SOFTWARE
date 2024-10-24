#include "../include/reverse.h"
char *reverse(char *dest, const char *src)
{
    //FIX ME
    const char* curr = src;
    int len = 0;

    while(*curr != '\0'){
	    len++;
	    curr++;
    }

    for(int i = 0; i < len; i++){
	    dest[i] = src[len - 1 - i];
    }

    dest[len] = '\0'; //end of string
    return dest;


}
