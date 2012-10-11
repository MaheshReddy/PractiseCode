// defines the chat structure to be used for communication.
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
#define MAX_QUEUE_SIZE 80

#define PRXY_SER1_IP "127.0.0.1"
#define PRXY_SER2_IP "127.0.0.1"
#define CLI1_IP "127.0.0.1"
#define CLI2_IP "127.0.0.1"
#define SERV_IP "127.0.0.1"

#define PRXY_SER1_UDP_PORT "8880"
#define PRXY_SER2_UDP_PORT "8881"
#define SERV_TCP_PORT "8882"
#define PRXY_SER1_TCP_PORT "8883"
#define PRXY_SER2_TCP_PORT "8884"
#define CLI1_UDP_PORT "8885"
#define CLI2_UDP_PORT "8886"


#define DEBUG(LEVEL,MSG) {\
        printf(MSG);\
}

typedef struct chat_msg_t{
	char sender[20]; // Unique Sender Id.
	char recv[20]; //Unique Receiver Id.
	char msg[40]; // Msg to be sent
}chat_msg;

void print_chat_msg(chat_msg *msg);

int convertToNetaddress(int af,const char* src,void* dest);

int udpWriter(char *ip, char* port, char* msg);

int tcpWriter(char *ip, char* port, char* msg);

int udpReader(char *ip, char* port, void (func)(chat_msg* buf));

int tcpReader(char *ip, char* port,  void (func)(chat_msg* buf));
