#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

void *func_thrd1(void *arg){
	pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
	printf("In thrd1 %s\n",(char *)arg);
	sleep(10);
	printf("In thrd1 %s\n",(char *)arg);
}

int main(int argc,char **argv){
	
	pthread_t thrd1 , thrd2;
	int r;
	char *str1 = "Thread1";
	char *str2 = "Thread2";

	if((r = pthread_create(&thrd1,NULL,func_thrd1,(void *)str1 ))<0){
		perror("pthread_create:");
		return r;
	};

	if((r = pthread_create(&thrd1,NULL,func_thrd1,(void *)str2))<0){
		perror("pthread_create:");
		return r;
	};
	pthread_join(thrd1,NULL);
	//pthread_join(thrd2,NULL);
	return 0;
}
