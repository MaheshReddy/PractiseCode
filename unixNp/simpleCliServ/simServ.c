#include<stdio.h>
#include<sys/socket.h>
#include<sys/signal.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define MAX_QUEUE_SIZE 1024
#define BUFFER_SIZE 1024


int startTcpServer(char** argv);
int startUDPServer(char** argv);
void catchSigInt(int arg){
	printf("Caught sigint exiting %d\n",arg);
	exit(0);
}
int main(int argc,char** argv){
	if(argc != 3){
	printf("Usage: ./a.out <SOCK_STREAM,SOCK_DGRAM> <PORT>\n");
	}
	signal(SIGINT,&catchSigInt);
	if(!strncmp("SOCK_STREAM",argv[1],11))
		startTcpServer(argv);
	else if(!strncmp("SOCK_DGRAM",argv[1],11))
		startUDPServer(argv);
	return 0;
}

int startTcpServer(char** argv)
{
	struct sockaddr_in sockaddr;
	int err;
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family=PF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(atoi(argv[2]));
	int sock_fd = socket(PF_INET,SOCK_STREAM,0);

	if((err=bind(sock_fd,(struct sockaddr* )&sockaddr,sizeof(sockaddr)))<0){
		perror("bind:");
		exit(-1);
	}

	if((err=listen(sock_fd,MAX_QUEUE_SIZE))<0){
		perror("listen:");
		exit(-1);
	}

	char buffer[BUFFER_SIZE] = "Mahesh Is awesome";

	while(1){
		int fd = accept(sock_fd,NULL,NULL);
		write(fd,buffer,BUFFER_SIZE);
		close(fd);
	}
	return 0;
}

int startUDPServer(char** argv){
	struct sockaddr_in sockaddr;
	int sock_fd;
	sockaddr.sin_family=PF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(atoi(argv[2]));
	sock_fd = socket(PF_INET,SOCK_DGRAM,0);
	int err;

	if((err=bind(sock_fd,(struct sockaddr* )&sockaddr,sizeof(sockaddr)))<0){
		perror("bind:");
		exit(-1);
	}


	char buffer[BUFFER_SIZE] = "Mahesh Is awesome";

	while(1){
		struct sockaddr_in sockaddr;
		socklen_t len;
		int bytesRead;
		if((bytesRead = recvfrom(sock_fd,buffer,BUFFER_SIZE,MSG_WAITALL,(struct sockaddr* )&sockaddr,&len))<0)
			perror("resvfrom:");
		buffer[bytesRead]=0;
		printf("Got Message '%s' from %d\n",buffer,ntohl(sockaddr.sin_addr.s_addr));
	}
	return 0;
}
