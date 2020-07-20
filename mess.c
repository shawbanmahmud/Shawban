#include "acc.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void createMail(char*, int);
static void *listMailbox();
static void *sendMessage();
static void *getMailbox();
static void *readEmail();
static void *deleteEmail();
static void *quit();
static struct client_list cl;
void *selection(void *arg);
static int structcount = 10;


struct client_list
{
	char client_name[30];
	time_t clientJoined;
	int ipAddr;
	int portNum;
	int numOfMail;
	//struct mailbox_info info[structcount];
};

struct mailbox_info
{
	int email_id;
	char sender_name;
	time_t time;
	char status;
};


int main(int argc, char **argv)
{
 int listenfd, *iptr;
 pthread_t tid;
 socklen_t addrlen, len;
 struct sockaddr *cliaddr;

 if (argc == 2)
  listenfd = Tcp_listen(NULL, argv[1], &addrlen);
 else if (argc == 3)
  listenfd = Tcp_listen(argv[1], argv[2], &addrlen);
 else
  err_quit("usage: tcpserv01 [ <host> ] <service or port>");

 cliaddr = (struct sockaddr *) Malloc(addrlen);

 for ( ; ; )
 {
  len = addrlen;
  iptr = (int *) Malloc(sizeof(int));
  *iptr = Accept(listenfd, cliaddr, &len);
  Pthread_create(&tid, NULL, selection, iptr);
 }
}


void *selection(void *arg)
{
        int connfd;
        int i;
	char line[20];
	char str[20];
	char str2[20];
	char *tok;
	char Make[50] = "make";
	char Quit[10] = "quit\n";
	char List[10] = "list";
	char Send[10] = "send";
	char Get_mailbox[20] = "get_mailbox";
	char Read[10] = "read";
	char Delete[10] = "delete";
	char strname[20], temp[10];
	printf("Created this thread: %d \n", pthread_self());
	sleep(5);
	connfd = *((int*)arg);
	free(arg);
	ssize_t		n;
        pthread_detach(pthread_self());
	
	while(1)
	{
	n = Readline(connfd, line, MAXLINE);
	printf("%s", line);
	sscanf(line, "%s %s", temp, strname);
	/*tok = strtok(line, " ");
	strcpy(str,tok);
	printf("test2%s", line);
	tok = strtok(NULL, "\n");
	printf("test3%s", line);
	strcpy(str2,tok);
	printf("test4%s", line);*/
	

	if(strcmp(temp,Make) == 0)
	{
		printf("test5 %s\n", strname);
		createMail(strname, connfd);
		
	}
	else if(strcmp(line,Quit) == 0)
	{
		goto s;
		
	}else if(strcmp(line,Send) == 0)
	{
		sendMessage();
	}else if(strcmp(line,Get_mailbox) == 0)
	{
		getMailbox();
	}else if(strcmp(line,Read) == 0)
	{
		readEmail();
	}else if(strcmp(line,Delete) == 0)
	{
		deleteEmail();
	}else if(strcmp(line,List) == 0)
	{
		listMailbox();
	}

	}

	
        s: Close(connfd);
	i--;
	pthread_exit(pthread_self());
	
}
        
void createMail(char *str2, int connfd)//create mailbox for client
 {
   struct tm *currentTime;
   FILE *fptr;
   printf("test");
   mkdir(str2, 0700);
   Writen(connfd, "done\n", MAXLINE);
   printf("Mail created!\n");
   time(&cl.clientJoined);
   currentTime = localtime(&cl.clientJoined);
   cl.ipAddr = 127000;
   cl.numOfMail = 0;
   cl.portNum = 52049;
   fptr = fopen("clientList.txt", "a+");

	 while(fptr != NULL)
	 {
		 	fprintf(fptr, "%s", cl.client_name);
			fprintf(fptr, "%d", cl.ipAddr);
			fprintf(fptr, "%d", cl. numOfMail);
			fprintf(fptr, "%d", cl. portNum);
	 }
 }


 static void *listMailbox() //list down the mailbox available
 {
	 	char *filename = "client_list.txt";
		FILE *fptr;
		int count = 0;
		char str[100];

		fptr = fopen(filename, "r");
		fgets(str, MAXLINE, fptr);
		printf("Mail:%s", str);
		fclose(fptr);

 }

 static void *sendMessage() //compose message
 {
	 	int mail_ID;
		char *client_name;
		char message[50];
		char *file = "client_list.txt";
		FILE *fptr;
                char *mail;

		printf("Please enter your name");
		scanf("%s", client_name);
		fptr = fopen(file, "w");

		printf("Please enter the recipient's name");
		scanf("%s", client_name);
		fptr = fopen(file, "w");

		printf("Please enter your message");
		scanf("%s", message);
		fptr = fopen(mail, "w");
		fclose(fptr);

 }

 static void *getMailbox() //Get mailbox
 {
    char mailboxName[20];
    char *path = NULL;
    FILE *fp;
		char str[100];
    int count = 0;

    while(strlen(mailboxName) < 21)
    {
        printf("Please enter your name");
        scanf("%s", mailboxName);
        path = (char*)(mailboxName);
        printf("%s", path);

				chdir(path);
				fp = fopen("mailbox_info.txt", "r");
				fclose(fp);
		}

 }

 static void *readEmail() //reading mail
 {
    char mailboxName[20];
    int mail_ID;
    char mail[100];
		FILE *fp;
        char *path;

    printf("Please enter your name");
    scanf("%s", mailboxName);
		if(strlen(mailboxName) < 20)
		{
			path = (char*)(mailboxName);
			printf("%s", path);

		}
		else
		{
				printf("Please enter name length of less than 20 words");
		}

		fp = fopen(mail, "r");
		fclose(fp);
  }

static void *deleteEmail() //delete email
{
	char mailboxName[20];
	int mail_ID;
	char *file = "client_list.txt";
	char mail[100];
	FILE *fp;
        char *path;

	printf("Please enter your name");
	scanf("%s", mailboxName);
	fp = fopen(file, "r");

	if(strlen(mailboxName) < 20)
	{
		path = (char*)(mailboxName);
		printf("%s", path);

	}
	else
	{
			printf("Please enter name length of less than 20 words");
	}

	fclose(fp);
	remove(mail);
	printf("Mail deleted successfully");
}

static void *quit() //quit the application
{
		printf("Bye bye!");
		exit(1);
}
