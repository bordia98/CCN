#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{
    char buff[2000];
    int sockfd,connfd,len;

struct sockaddr_in servaddr,cliaddr;

// create socket in client side
sockfd = socket(AF_INET, SOCK_DGRAM, 0);

if(sockfd==-1)
{
    printf(" socket not created in client\n");
    exit(0);
}
else
{
    printf("socket created in  client\n");
}


bzero(&servaddr, sizeof(servaddr));

servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY; // ANY address or use specific address
servaddr.sin_port = htons(7802);  // Port address


    printf("Type ur  UDP client message\n");
    scanf("%s",buff);

// send  msg to server
len=sizeof(struct sockaddr);

sendto(sockfd, buff, strlen(buff), 0,(struct sockaddr *)&servaddr, sizeof(struct sockaddr));
char file_buffer[2000];

    if (recvfrom(sockfd,file_buffer,2000,0,  (struct sockaddr *)&servaddr, &len)<0)
    {
      printf("error in recieving the file\n");
      exit(1);
    }

  char new_file[]="copied";
  strcat(new_file,buff);
  FILE *fp;
  fp=fopen(new_file,"w+");
  if(fwrite(file_buffer,1,sizeof(file_buffer),fp)<0)
    {
      printf("error writting file\n");
      exit(1);
    }

  printf("The file is copied\n");
  //close client side connection
    close(sockfd);

return(0);
}
