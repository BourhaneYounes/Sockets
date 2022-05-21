#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>

int main(void){

    int socketClient = socket(AF_INET, SOCK_STREAM, 0), bytes_recv;
    char send_data[1024], rcv_data[1024];
    struct sockaddr_in addrServer; 
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3000);

    connect(socketClient, (const struct sockaddr*)&addrServer, sizeof(addrServer));
    printf("connection\n");

    recv(socketClient, rcv_data, 1024, 0);

    close(socketClient);
    

    return 0;
}