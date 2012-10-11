#include "chat_infra.h"
#include<pthread.h>

int startTcpServer(char** argv);
int startUDPServer(char** argv);
void catchSigInt(int arg){
	printf("Caught sigint exiting %d\n",arg);
	exit(0);
}

void handl_udp_from_cli(chat_msg* msg){
	tcpWriter(SERV_IP,SERV_TCP_PORT,(char *)msg);
}

void handl_tcp_from_serv(chat_msg* msg){
	if(!(strcmp(msg->recv,"client1")))
		udpWriter(CLI1_IP,CLI1_UDP_PORT,(char *)msg);
}

int main(int argc,char** argv){
	signal(SIGINT,&catchSigInt);
	int r=0;
	pid_t udp_pid = fork();
	if (udp_pid) // Run Udp server in parent
		udpReader(PRXY_SER1_IP,PRXY_SER1_UDP_PORT,handl_udp_from_cli);
	else 
		tcpReader(PRXY_SER1_IP,PRXY_SER1_TCP_PORT,handl_tcp_from_serv);
	return 0;
}
