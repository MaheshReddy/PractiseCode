#include<stdio.h>
#include<errno.h>
#include<sched.h>
#include<string.h>
int my_pipe(char* prog1, char* prog2);
int main(int argc, char** argv){
	if(argc != 3 ){
		printf("Usage:./a.out cmd1 cmd2\n");
		return -1;
	}
	my_pipe(argv[1],argv[2]);
	return 0;
}
int search_path(char* input,char** output){
	int i=0;
	printf("Copying\n");
	char* path[2]={"/usr/bin/\0","/bin/\0"};
	printf("Copying\n");
	for(i=0;i<2;i++){
		printf("Copying %s %s\n",path[i],input);
		printf("Copying %s\n",strcat(path[i],input));
		FILE* fp;
		if((fp = fopen(strcat(path[i],input),"r")) != NULL){
			printf("Copying\n");
			*output = strcat(path[i],input);
			printf("Copying1\n");
			fclose(fp);
			return 0;
		}
		fclose(fp);
	}
}

int my_pipe(char* prog1,char* prog2){
	extern char **environ;
	int fds[2],r;

	if((r=search_path(prog1,&prog1))<0){
		printf("Not able to open the executable\n");
		return -1;
	}

	if ((r=pipe(fds))<0){
		perror("Creating Pipe:");
		return errno;
	}

	int pid1,pid2;
	pid1 = fork();
	if( pid1 ){ // I am parent
		pid2 = fork(); // forking the other child
		if( pid2 ){ // in parent again
			close(fds[0]);
			close(fds[1]);
		}
		else{
			if((r=dup2(fds[0],0))<0){
				perror("dup2 error:");
				return errno;
			}
			close(fds[1]);
			close(fds[1]);
			char* args[2]= {"more",0};
			if((r=execve("/usr/bin/more",args,environ))<0){
				perror("execve error:");
				return errno;
			}
		}
	}
	else{
		if((r=dup2(fds[1],1))<0){
			perror("dup2 error:");
			return errno;
		}
		close(fds[0]);
		close(fds[2]);
		char* args[2]= {"ls",0};
		if((r=execve("/bin/ls",args,environ))<0){
			perror("execve error:");
			return errno;
		}
	}
	waitpid(pid1);
	waitpid(pid2);
	return 0;
}

