#include "chat_infra.h"
#include<stdio.h>
#define CLI_UNQ_ID "client1"


int main(int argc,char **argv){
	chat_msg msg; 
	if(argc!=2){
		printf("Usage: ./a.out recv \n"); 
		return(-1);
	}
	pid_t udp_pid = fork();
	if(udp_pid){
		printf("Start Chatting:\n");
		while(1){
			chat_msg msg; 
			strcpy(msg.sender,CLI_UNQ_ID);
			strcpy(msg.recv,argv[1]);
			scanf("%s",(msg.msg));
			//print_chat_msg(&msg);
		    udpWriter(PRXY_SER1_IP,PRXY_SER1_UDP_PORT,(char*)&msg);
		}
	}
	else{
		udpReader("localhost","8810",print_chat_msg);
	}
	return 0;
}
