#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int Serversocket, new_socket;
    	struct sockaddr_in server, client;
    	int sizeOfStruct = sizeof(struct sockaddr_in);
    	char message[5000],reply[5000];

    	// Create socket
    	Serversocket = socket(AF_INET, SOCK_STREAM, 0);
    	if(Serversocket < 0) {
       		 perror("socket error!");
    	}
    
    	// Prepare sock_addr
    	server.sin_family = AF_INET;
    	server.sin_addr.s_addr = INADDR_ANY;
    	server.sin_port = htons(8890);

    	// Bind socket
    	if(bind(Serversocket, (struct sockaddr *)&server, sizeof(server)) < 0) {
        	perror("bind error!");
    	}

    	// Listen for connection
   	listen(Serversocket, 3);
//	puts("--Waiting for connection from any client--");



    //	 Accept incoming connection    
	while(new_socket = accept(Serversocket, (struct sockaddr *)&client, (socklen_t*)&sizeOfStruct)) {
		
		
        	// Receive message from client
        	recv(new_socket, reply, 5000, 0);
       		printf("CLIENT: %s ", reply);

        	// Send message  from client
		printf("SERVER :");
        	fgets(message, 5000, stdin);
        	send(new_socket, message, 5000, 0);
	
	    }
    if(new_socket < 0)
        perror("new socket error");

    return 0;
}
