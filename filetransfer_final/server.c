#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 10000

int main(int argc, char **argv){
	FILE *fp;
	char s[80], file[80];
	struct sockaddr_in servaddr, cliaddr;

	int listenfd, connfd, clilen;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);

	bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

	listen(listenfd, 1);
	clilen = sizeof(cliaddr);
	connfd = accept(listenfd, (struct sockaddr*)&cliaddr, &clilen);

	printf("Client connected!");

	read(connfd, file, 80);
	fp = fopen(file, "r");
	printf("File name: %s", file);
	while(fgets(s, 80, fp) != NULL){
		printf("%s", s);
		write(connfd, s, sizeof(s));
	}

	close(listenfd);
	fclose(fp);

	return 0;
}
