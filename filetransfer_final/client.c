#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>

#define PORT 10000

int main(int argc, char **argv){
	char filename[80], s[80];
	struct sockaddr_in servaddr;

	int sockfd;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
	connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	printf("Enter a filename: ");
	scanf("%s", filename);
	write(sockfd, filename, sizeof(filename));
	printf("Data from server: \n");

	while(read(sockfd, s, 80) != 0){
		fputs(s, stdout);
	}

	close(sockfd);

	return 0;
}
