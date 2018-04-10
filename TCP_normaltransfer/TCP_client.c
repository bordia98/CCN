#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(){

	//creating the socket
	int network_socket;
	network_socket = socket(AF_INET,SOCK_STREAM,0);
	 
	//specify an address for the socket
	
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9000);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	//connecting with the server socket
	int connection_status = connect(network_socket, (struct sockaddr * ) &server_address,sizeof(server_address));

	//check for the error with the connection
	if (connection_status == -1 ){
		printf("There is an error in connecting with the server\n");
		return 0;
	 }
	char server_response[256];
	//receiving from the socket
	int receivestatus = recv(network_socket,&server_response,sizeof(server_response),0);
	//printing the data from the server we got
	if (receivestatus==-1){
		printf("Error in receiving data from the server\n");
		return 0;
	}
	printf("The server send the data : %s\n",server_response);
	// and then close the socket
	close(network_socket);
	return 0;
}
