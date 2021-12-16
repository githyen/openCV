#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>

void error_control(char *mes);

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

	sock=socket(PF_INET, SOCK_STREAM,0);

	if(sock == -1)
		error_control("socket () error");

	memset(&serv_addr,0,sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) == -1)
		error_control("connect() error");


	char c;
	while(1)
	{
		str_len = read(sock,(char *)&c,1);

		if(str_len <= 0)
		{
			printf("not data \n");
			break;
		}

		if(str_len == -1) {
			error_control("read () error");
			break;
		}

		write(1,&c,1);
		sleep(1);
	}

	close(sock);
	return 0;
}


void error_control(char *mes)
{
	fputs(mes,stderr);
	fputc('\n',stderr);
	exit(1);
}


