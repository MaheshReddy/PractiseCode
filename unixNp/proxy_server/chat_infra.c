#include "chat_infra.h"

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

int tcpWriter(char *ip, char* port, char* msg){
	int err;
	struct sockaddr_in serv_addr;
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;

	if((err=convertToNetaddress(AF_INET, ip, &serv_addr.sin_addr))<=0){
			return err;
	}

	serv_addr.sin_port = htons(atoi(port));
	int s_fd = socket(PF_INET,SOCK_STREAM,0);

	if((err=connect(s_fd,(const struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0){
		perror("connect:");
		return err;
	}
	write(s_fd,msg,BUFFER_SIZE);
	close(s_fd);
	return 0;
}

int udpWriter(char *ip, char* port, char* msg){
	int sock_fd = socket(PF_INET,SOCK_DGRAM,0);
	struct sockaddr_in sockaddr;
	int err;
	if((err=convertToNetaddress(AF_INET,ip,&sockaddr.sin_addr))<0)
		return err;
	sockaddr.sin_port = htons(atoi(port));
	sockaddr.sin_family = PF_INET;
	//char buffer[BUFFER_SIZE] = "Message from UDP Client";
	sendto(sock_fd,msg,BUFFER_SIZE,0,(struct sockaddr* )&sockaddr,sizeof(sockaddr));
	//inet_pton(PF_INET,argv[2],&(sockaddr.sin_addr.s_addr));
	return 0;
}

int tcpReader(char *ip, char* port, void (func)(chat_msg* buf)){
	struct sockaddr_in sockaddr;
	int err;
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family=PF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(atoi(port));
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
		int readLen=0;
		char readbuf[BUFFER_SIZE];
		while((readLen=read(fd,readbuf,BUFFER_SIZE))>0){
			readbuf[BUFFER_SIZE]=0;
			//print_chat_msg((chat_msg*) readbuf);
			if(func)
				func((chat_msg* )readbuf);
		}
		close(fd);
	}
	return 0;
}

int udpReader(char *ip, char* port, void (func)(chat_msg* buf)){
	struct sockaddr_in sockaddr;
	int sock_fd;
	sockaddr.sin_family=PF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(atoi(port));
	sock_fd = socket(PF_INET,SOCK_DGRAM,0);
	int err;

	if((err=bind(sock_fd,(struct sockaddr* )&sockaddr,sizeof(sockaddr)))<0){
		perror("bind:");
		exit(-1);
	}


	char buffer[BUFFER_SIZE] = "";

	while(1){
		struct sockaddr_in sockaddr;
		socklen_t len;
		int bytesRead;
		if((bytesRead = recvfrom(sock_fd,buffer,BUFFER_SIZE,MSG_WAITALL,(struct sockaddr* )&sockaddr,&len))<0)
			perror("resvfrom:");
		buffer[bytesRead]=0;
		//print_chat_msg((chat_msg*)(buffer));
		if(func)
			func((chat_msg*) buffer);
		// Now send the mesg using tcp to main serv
		//printf("Got Message '%s' from %d\n",buffer,ntohl(sockaddr.sin_addr.s_addr));
	}
	return 0;
}
void print_chat_msg(chat_msg *msg){
	printf("Sender: %s \t Receiver: %s\n Msg: %s\n",msg->sender,msg->recv,msg->msg);
}
