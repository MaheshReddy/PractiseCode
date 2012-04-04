#include<stdio.h>

/**
  Returns true if str is interleaving of str1 and str2.
  For references see gfg 	 goo.gl/R0dtr
**/  
int is_string_inter_leave(char* str,char* str1,char* str2,int len,int len1,int len2){
	if(len ! = len1+len2)
		return 0;

	if(len1 > 0){
		if(str[len-1] == str1[len1-1])
			return is_string_inter_leave(str,str1,str2,len-1,len1-1,len2);
	}

	if(len2 > 0){
		if(str[len-1] == str2[len2-1])
			return is_string_inter_leave(str,str1,str2,len-1,len1,len2-1);
	}

	if(len == 0)
		return 1;
	else
		return 0;
}
