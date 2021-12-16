#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/time.h>
#define OUT(x...) fprintf(stderr,x)

//pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

void error_control(char *mes);
void *send_thread(void *);
void *rcv_thread(void *);

void get_time()
{
	struct tm *gt;
	time_t current;
	time(&current);

	gt=gmtime(&current);
	OUT("%d.%d.%d %d시%d분%d초:",gt->tm_year+1900,gt->tm_mon,gt->tm_mday,gt->tm_hour+2,gt->tm_min,gt->tm_sec);
	return;
}

	

int main(int argc, char **argv)
{
	int sock;

	struct sockaddr_in serv_addr;
	char mes[30];
	int str_len;

	if(argc!=3)
	{
		perror("<IP> <PORT>");
		exit(1);
	}


	pthread_t tid[2];

	sock=socket(PF_INET, SOCK_STREAM,0);

	if(sock == -1)
		error_control("socket () error");

	memset(&serv_addr,0,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
		error_control("connect() error");

	pthread_create(&tid[0],NULL,rcv_thread,(void *)&sock);
	pthread_create(&tid[1],NULL,send_thread,(void *)&sock);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	close(sock);
	return 0;
}

void *rcv_thread(void *arg)
{
	int sock=*((int *)arg);
	char msg[1024];
	int msg_len;
	while(1)
	{
		get_time();
		OUT("server:");
		msg_len=read(sock,msg,1024);
		if(msg_len == -1) {error_control("read () error"); return NULL; }
		msg[msg_len]='\0';
		write(1,msg,strlen(msg));
	}
	return NULL;
}

void *send_thread(void *arg)
{
	int sock=*((int *)arg);
	char msg[1024];
	while(1)
	{
		get_time();
		OUT("client :");
		read(0,msg,sizeof(msg));
		if(strcmp(msg,"exit")==0) { close(sock); exit(0); }
		
		write(sock,msg,strlen(msg));
	}

	return NULL;
}

void error_control(char *mes)
{
	fputs(mes,stderr);
	fputc('\n',stderr);
	exit(1);
}


