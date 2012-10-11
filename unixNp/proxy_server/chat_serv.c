#include "chat_infra.h"

void catchSigInt(int arg){
	printf("Caught sigint exiting %d\n",arg);
	exit(0);
}
void handl_tcp_from_prxy(chat_msg* msg){
	tcpWriter(PRXY_SER1_IP,PRXY_SER1_TCP_PORT,(char *)msg);
}
int main(int argc,char** argv){
	signal(SIGINT,&catchSigInt);
	tcpReader(SERV_IP,SERV_TCP_PORT,handl_tcp_from_prxy);
	return 0;
}
