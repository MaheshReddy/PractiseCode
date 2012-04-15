#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ASCII_LOWER 97


void build_diction();
char eng[26]={"yhesocvxduiglbkrztnwjpfmaq"};
//char eng[26];
char gool[26]={"yhesocvxduiglbkrztnwjpfmaq"};
//char gool[26];
int main(){
	//build_diction();
	//return 1;
	int no_tc = 0;
	scanf("%d",&no_tc);
	getchar();
	char out_put[no_tc][101];
	memset(out_put,0,sizeof(char)*101*no_tc);
	int ctr = 0;
	while (no_tc--){
		char inputLine[101],ch=' ';
		int len = 0;
		ch = getchar();
		while(ch != '\n'){
			if (ch != ' ')
				out_put[ctr][len++] = eng[ch - ASCII_LOWER];	
			else
				out_put[ctr][len++]=ch;
			ch = getchar();
		}
		out_put[ctr++][len]='\0';
		//printf("%s\n",out_put[ctr-1]);
		//printf("Case #%d: %s\n",ctr,out_put[ctr-1]);
		len = 0;
		}
	int i =0 ;
	for(i=0;i<ctr;i++)
		printf("Case #%d: %s\n",i+1,out_put[i]);
	}


void build_diction(){
	int no_tc = 0;
	scanf("%d",&no_tc);
	getchar();
	while (no_tc--){
		char inputLine[101],inputLine1[101],ch=' ';
		int len = 0;
		ch = getchar();
		while(ch !='\n'){
			inputLine[len++] =ch;	
			ch = getchar();
		}
		inputLine[len]='\0';
		len = 0;
		ch = getchar();
		while (ch !='\n'){
			inputLine1[len++]=ch;
			ch = getchar();
		}
		inputLine1[len]='\0';
		//printf("%s\n",inputLine);
		//printf("%s\n",inputLine1);
		while (--len){
			if (inputLine1[len] == ' ')
				continue;
			eng[inputLine[len] - ASCII_LOWER] = inputLine1[len];
			gool[inputLine1[len] - ASCII_LOWER] = inputLine[len];
			//printf("%c %c %d\n",inputLine[len],inputLine1[len],inputLine1[len] - ASCII_LOWER);
		}
	}
	int len=0;
		for (len =0 ; len <26;len++)
			printf("%c:%c ",ASCII_LOWER+len,eng[len]);
			//printf("%c",eng[len]);
	printf("\n");
		for (len =0 ; len <26;len++)
			printf("%c:%c ",ASCII_LOWER+len,gool[len]);
			//printf("%c",gool[len]);
	printf("\n");
}
