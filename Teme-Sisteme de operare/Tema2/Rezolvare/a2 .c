#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "a2_helper.h"
#include <pthread.h>
#include <stdbool.h>
pthread_mutex_t lock,lock2;
bool t53begun=false,t54ended=false;
void p5();
void p6();
void p7();
typedef struct paramm
{
	int id;
}param;
param p[100];
pthread_t thread[100];
void*p4thread(void*pp)
{
	param* p=(param*)pp;
	int id=p->id;
	info(BEGIN,4,id);
	pthread_mutex_lock(&lock);
	info(END,4,id);
	pthread_mutex_unlock(&lock);
	return NULL;
}
void* p5thread(void*pp)
{
	param* p=(param*)pp;
	int id=p->id;

	if(id==4)
	{
		for(;!t53begun;);
	}
	info(BEGIN,5,id);
	if(id==3)
	{
		pthread_mutex_lock(&lock2);
		t53begun=true;
		pthread_mutex_unlock(&lock2);
	}
	if(id==3)
	{
		for(;!t54ended;);
	}
	pthread_mutex_lock(&lock);
	info(END,5,id);
	pthread_mutex_unlock(&lock);
	if(id==4)
	{
		pthread_mutex_lock(&lock2);
		t54ended=true;
		pthread_mutex_unlock(&lock2);
	}
	return NULL;
}
void p2(){
	info(BEGIN, 2, 0);
	if(!fork())
	{
		p5();
		return;
	}
	if(!fork())
	{
		p7();
		return;
	}
	wait(0);
	wait(0);
	info(END, 2, 0);
}
void p3(){
	info(BEGIN, 3, 0);
	if(!fork())
	{
		p6();
		return;
	}
	wait(0);
	info(END, 3, 0);
}
void p4(){
	info(BEGIN, 4, 0);
	pthread_mutex_init(&lock,0);
	for(int i=0;i<37;i++)
	{
		p[i].id=i+1;
		pthread_create(&thread[i],0,p4thread,(void*)&p[i]);
	}
	for(int i=0;i<37;i++){
		pthread_join(thread[i],0);
	}
	info(END, 4, 0);
}
void p5(){

	info(BEGIN, 5, 0);
	pthread_mutex_init(&lock,0);
	pthread_mutex_init(&lock2,0);
	for(int i=0;i<5;i++)
	{
		p[i].id=i+1;
		pthread_create(&thread[i],0,p5thread,(void*)&p[i]);
	}
	for(int i=0;i<5;i++){
		pthread_join(thread[i],0);
	}
	info(END, 5, 0);
}
void p6(){
	info(BEGIN, 6, 0);

	info(END, 6, 0);
}
void p7(){
	info(BEGIN, 7, 0);

	info(END, 7, 0);
}
int main(){
    init();
    info(BEGIN, 1, 0);
    if(!fork())
	{
    	p2();
    	return 0;
	}
    if(!fork())
	{
    	p3();
		return 0;
	}
	if(!fork())
	{
		p4();
		return 0;
	}
	wait(0);
	wait(0);
	wait(0);
    info(END, 1, 0);
    return 0;
}
