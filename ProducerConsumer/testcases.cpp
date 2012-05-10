#include"NamedMutex.h"
#include<iostream>
#include<sys/wait.h>
#include<pthread.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

using namespace std;

int print_to_file(char *sem_name,int flag){
	char test_file[]= "test_file";
	NamedMutex lck(sem_name);
	if (flag)
		lck.setlkType();
	for (int i=0;i<5;i++){
		FILE *fp = fopen(test_file,"a");
		if (fp == NULL){
			perror("fopen error:");
			return -1;
		}
		sleep((random() % 10));
		lck.lock();
		fprintf(fp,"LOCKED\n");
		if(!flag)
			fprintf(fp,"%d:%d\n",getpid(),i);
		else
			fprintf(fp,"%ld:%d\n",(unsigned long)pthread_self(),i);
		sleep((random() % 10));
		fprintf(fp,"UNLOKCING\n");
		lck.unlock();
		fclose(fp);
	}
	return 0;
}

void *thrd_print(void *name){
	print_to_file((char *)name,1);
}

int test_multi_process(){
	int no_pro = 1;
	char sem_name[MAXNAMELEN];
	cout<<"Enter number of process:";
	scanf("%d",&no_pro);
	cout<<"Enter name of the semaphore:";
	scanf("%s",sem_name);
	pid_t pid[no_pro];
	for (int i=0;i<no_pro;i++){
		pid[i] = fork();
		if(!pid[i]){
			print_to_file(sem_name,0);
			exit(0);
		}
	}
	for (int i=0;i<no_pro;i++){ // Now I wait for my child process
		int status;
		waitpid(pid[i],&status,WUNTRACED);
	}
}

int test_multi_thread(){
	int no_thrd = 1;
	char sem_name[MAXNAMELEN];
	cout<<"Enter number of threads:";
	scanf("%d",&no_thrd);
	cout<<"Enter name of the semaphore:";
	scanf("%s",sem_name);
	pthread_t thrds[no_thrd];
	for (int i=0;i<no_thrd;i++){
		pthread_create(&(thrds[i]),NULL,thrd_print,(void *)sem_name);
	}
	// Now joining the threads
	for (int i=0;i<no_thrd;i++){
		pthread_join(thrds[i],NULL);
	}
}

int main(int argc,char **argv){
	if (argc != 2){
		cout<<"Usage ./a.out P/T. P for multiproces and T for multithreaded test case"<<endl;
		return -1;
	}
	switch (argv[1][0]){
		case 'P':
			test_multi_process();
			break;
		case 'T':
			test_multi_thread();
			break;
		default:
			cout<<"Invalid arg"<<endl;
	}
	return 0;

}
