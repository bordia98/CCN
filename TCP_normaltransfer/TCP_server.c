#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){

	char server_response[256] = "You are now connected to the server";
	
	//Creating the server socket
	int server_socket;
	server_socket = socket( AF_INET,SOCK_STREAM,0);

	//defining the server address
	struct sockaddr_in server_address;
	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = INADDR_ANY;

	// binding the socket
	int binding_status = bind(server_socket, (struct sockaddr*) &server_address,sizeof(server_address));


	if (binding_status ==-1){
		printf("Error in binding the socket\n");
		return 0;
	}
	
	listen(server_socket,5);

	int client_socket;
	client_socket = accept(server_socket,NULL,NULL);
	//send the message
	send(client_socket,server_response,sizeof(server_response),0);

	close(server_socket);
	return 0;
}