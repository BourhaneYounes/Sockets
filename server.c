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

void* function(void* arg){
    int socket = *(int*)arg;
    char msg[] = "nom :";
    send(socket, msg,strlen(msg)+1, 0);
    recv(socket, msg, 7, 0);
    printf("%s\n", msg);
    close(socket);
    free(arg);
    pthread_exit(NULL);
}


int main(void){

    int socketServer = socket(AF_INET, SOCK_STREAM, 0);
    char msg[] = "hello world";
    struct sockaddr_in addrServer;
    addrServer.sin_addr.s_addr = inet_addr("127.0.0.1");
    addrServer.sin_family = AF_INET;
    addrServer.sin_port = htons(3000);

    bind(socketServer, (const struct sockaddr *)&addrServer, sizeof(addrServer));
    printf("bind: %d\n", socketServer);

    listen(socketServer, 5);
    printf("listen\n");

    pthread_t threads[3];

    for (int i = 0; i<3; i++){
        struct sockaddr_in addrClient;
        socklen_t csize = sizeof(addrClient);
        int socketClient = accept(socketServer, (struct sockaddr *)&addrClient, &csize);
        printf("accept\n");

        printf("client: %d\n", socketClient);

        int *arg = malloc(sizeof(int));
        *arg = socketClient;
        pthread_create(&threads[i], NULL, function,arg);
    }

    for (int i = 0; i<3; i++){
        pthread_join(threads[i],NULL);
    }

    //send(socketClient, msg, 10,0);

    //close(socketClient);
    close(socketServer);
    printf("close \n");

    return 0;

}