#include<stdio.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include<netdb.h>
#include<sys/errno.h>
#include<stdlib.h>
#define ADDR_SIZE 14
#define LINE_LEN 1
#define BUFFER_SIZE 1024
int tcpClient(char** argv);
int udpClient(char** argv);
/**
	 A simple network time client for getting network time from either an Ip address or a host name.
  */
int main(int argc,char **argv){
	if(argc!=4){
		printf("Usage: ./a.out <SOCK_STREAM,SOCK_DGRAM> <IP> <PORT>\n");
		return(-1);
	}
	if(!strncmp("SOCK_STREAM",argv[1],11))
		return tcpClient(argv);
	if(!strncmp("SOCK_DGRAM",argv[1],11))
		return udpClient(argv);
	return 0;
}
int convertToNetaddress(int af,const char* src,void* dest){
	int err=0;
	if((err=inet_pton(af, src, dest))<=0){
		struct hostent* servname = gethostbyname(src);
		memcpy(dest,servname->h_addr_list[0],servname->h_length);
		if(errno<0){
			herror("gethostbyname:");
			return err;
		}
	}
	return err;
}
int tcpClient(char** argv){
	int err;
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	if((err=convertToNetaddress(AF_INET, argv[2], &serv_addr.sin_addr))<=0){
			return err;
	}

	serv_addr.sin_port = htons(atoi(argv[3]));
	int s_fd = socket(PF_INET,SOCK_STREAM,0);

	if((err=connect(s_fd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0){
		perror("connect:");
		return err;
	}

	char readbuf[LINE_LEN+1];
	int readLen;
	while((readLen=read(s_fd,readbuf,LINE_LEN))>0){
		readbuf[readLen]=0;
		printf("%s",readbuf);
	}
	printf("\n");
	return 0;
}

int udpClient(char** argv){
	int sock_fd = socket(PF_INET,SOCK_DGRAM,0);
	struct sockaddr_in sockaddr;
	int err;
	if((err=convertToNetaddress(AF_INET,argv[2],&sockaddr.sin_addr))<0)
		return err;
	sockaddr.sin_port = htons(atoi(argv[3]));
	sockaddr.sin_family = PF_INET;
	char buffer[BUFFER_SIZE] = "Message from UDP Client";
	sendto(sock_fd,buffer,BUFFER_SIZE,0,(struct sockaddr* )&sockaddr,sizeof(sockaddr));
	//inet_pton(PF_INET,argv[2],&(sockaddr.sin_addr.s_addr));
	return 0;
}
