#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
        int Clientsocket;
        struct sockaddr_in server;
	char message[5000],reply[5000];
 
        while(1) {

        // Create socket
        Clientsocket = socket(AF_INET, SOCK_STREAM, 0);
	
        if(Clientsocket == -1)
            perror("socket error");


        server.sin_addr.s_addr = inet_addr("192.168.1.14");
        server.sin_family = AF_INET;
        server.sin_port = htons(8890);

        // Connect to remote server
        if(connect(Clientsocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
       		 perror("connection error");
		 close(Clientsocket);
		 exit(EXIT_FAILURE);	
		}
//	puts("--Your socket is connected to server!--");


//	while(1) {
	 // Send  message to server
        printf("CLIENT :");
	fgets(message,5000, stdin);
        send(Clientsocket, message, 5000, 0);
 
        // Receive message from server
        recv(Clientsocket, reply,5000, 0);
        printf("SERVER: %s ", reply);


    }
    return 0;
}
