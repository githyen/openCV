#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<pthread.h>
#define OUT(x...) fprintf(stderr,x)

//pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond=PTHREAD_COND_INITIALIZER;


void error_handling(char *mes);
void *rcv_thread(void *);
void *send_thread(void *);
void get_time()
{
	struct tm *gt;
	time_t current;
	time(&current);
	gt=gmtime(&current);
	printf("%d.%d.%d %d시%d분%d초:",gt->tm_year,gt->tm_mon,gt->tm_mday,gt->tm_hour,gt->tm_min,gt->tm_sec);
	return;
}

int main(int argc,char **argv)
{

	int serv_sock;
	int clnt_sock;

	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;

	socklen_t clnt_addr_size;



	pthread_t tid[2];


	if(argc!=2)
	{
		printf("Uasge : %s ,<port>\n",argv[0]);
		exit(1);
	}


	serv_sock=socket(PF_INET,SOCK_STREAM,0);
	if(serv_sock==-1)
		error_handling("socket() error");

	memset(&serv_addr,0,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(atoi(argv[1]));

	if(bind(serv_sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
		error_handling("bind () error");

	if(listen(serv_sock,5) == -1)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock,(struct sockaddr *)&clnt_addr,&clnt_addr_size);

	if(clnt_sock == -1)
		error_handling("accept () error");



	pthread_create(&tid[0],NULL,rcv_thread,(void *)&clnt_sock);
	pthread_create(&tid[1],NULL,send_thread,(void *)&clnt_sock);

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);

	close(clnt_sock);
	close(serv_sock);
	

	return 0;
}

void *send_thread(void *arg)
{

	int c_sock=*((int *)arg);
	char msg[1024];

	while(1)
	{
		get_time();
		printf("server:");
		read(0,msg,1024);
		if(strcmp(msg,"exit")==0) { OUT("종료합니다\n"); break; }
		write(c_sock,msg,strlen(msg));
	}
	return NULL;
}

void *rcv_thread(void *arg)
{
	int c_sock=*((int *)arg);
	char msg[1024];

	int msg_len;
	while(1)
	{
		get_time();
		msg_len=read(c_sock,msg,1024);
		msg[msg_len]='\0';
		if(msg_len == -1) { error_handling("read () error"); break; }
		OUT("client : %s\n",msg);
	}
	return NULL;
}
void error_handling(char *mes)
{
	fputs(mes,stderr);
	fputc('\n',stderr);
	exit(1);
}
