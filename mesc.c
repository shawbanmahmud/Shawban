#include "acc.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>


int main(int argc, char **argv)
{

  int	sockfd;
	struct sockaddr_in servaddr; //specify an address for the socket

	if (argc != 3)
		printf("usage: tcpcli <IPaddress> <port number>");

	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	Connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

	
while(1)
{
  char option[MAXLINE];
  char line[20];
  int n;
  char Quit[10] = "quit\n";



  	printf("==========================================\n");
  	printf("             WELCOME TO MES-CLIENT        \n");
  	printf("       Please select the option desired   \n");
  	printf("					          \n");
  	printf("1) Make a mailbox			  \n");
  	printf("2) List of clients  			  \n");
  	printf("3) Send message                           \n");
  	printf("4) Get mailbox                            \n");
  	printf("5) Read  email				  \n");
    	printf("6) Delete email                           \n");
  	printf("7) quit                                   \n");

	printf("MES-C > ");
    	Fgets(option, MAXLINE, stdin);
	Writen(sockfd, option, MAXLINE);
	
	n = Readline(sockfd, line, MAXLINE);
	printf("%s\n",line);
	sleep(3);

	if(strcmp(option,Quit) == 0)
	{
		exit(0);
	}
	

	
}
}
