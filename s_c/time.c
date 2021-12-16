#include<stdio.h>
#include<time.h>

#define OUT(x...) fprintf(stderr,x)
int main(){

	time_t cur_time;
	time(&cur_time);


	char *get_time=ctime(&cur_time); // ctime-> 현재 시간의 초를 가져와서 문자열 시간으로 변환
	OUT("%s",get_time);

	struct tm *gt;  

	gt=gmtime(&cur_time); // gmtime -> 현재 시간의 초를 가져와서 tm 구조체 맴버 변수에 저장
	
	OUT("%d년 %d월 %d일 %d시 %d분 %d초\n",gt->tm_year+1900,gt->tm_mon,gt->tm_mday,gt->tm_hour-2,gt->tm_min,gt->tm_sec);
	return 0;
}
