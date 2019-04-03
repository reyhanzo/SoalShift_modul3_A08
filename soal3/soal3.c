#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid1, tid2, tid3, tid4; 
int wakeup_status=0;
int spirit_status=100;
int call_agmal;
int call_iraj;
int count_iraj=0;
int count_agmal=0;
int flag=0;
 
void *check_agmal(void *arg)
{
     while(1)
     {
	if(call_agmal==0)
	{
		sleep(10);
	}
    }
    
}

void *check_iraj(void *arg)
{
    while(1)
	{
	if(call_iraj==0)
		{
		sleep(10);
		}
	}
}

void *tambah_agmal(void *arg)
{
    wakeup_status+=15;
    if(wakeup_status>=100)
    {
	printf("Agmal terbangun, mereka bangun pagi dan berolahraga\n");
	flag=1;
    }
}

void *kurang_iraj(void *arg)
{
    spirit_status-=20;
    if(spirit_status<=0)
    {
	printf("Iraj ikut tidur, dan bangun kesiangan bersama Agmal\n");
	flag=1;
    }	
}
 
int main(void)
{
    char message[100];
    char temp;
    int message_agmal;
    int message_iraj;
    call_iraj=1;
    call_agmal=1;

    pthread_create(&(tid3), NULL, check_agmal, NULL);
    pthread_create(&(tid4), NULL, check_iraj, NULL);

    while(1)
    {
	if(flag==1)break;
	printf("Agmal WakeUp_Status = %d\n", wakeup_status);
	printf("Iraj Spirit_Status = %d\n", spirit_status);
	scanf("%[^\n]s", message);
	scanf("%c", &temp);
	message_agmal = strcmp(message, "Agmal Ayo Bangun");
	message_iraj = strcmp(message, "Iraj Ayo Tidur");

		
	if(count_agmal==3)
	{
		call_agmal=0;
	}

	if(message_agmal==0)
	{
		if(call_agmal==1)
		{
			pthread_create(&(tid1), NULL, tambah_agmal, NULL);
			count_iraj++;
			pthread_join(tid1, NULL);
		}

		else
		{
			printf("Iraj ayo Tidur disabled 10s\n");
			call_agmal=1;
			count_agmal=0;
		}

	}

	if(count_iraj==3)
	{
		call_iraj=0;
	}

	if(message_iraj==0)
	{
		if(call_iraj==1)
		{
			pthread_create(&(tid2), NULL, kurang_iraj, NULL);
			count_agmal++;
			pthread_join(tid2, NULL);
		}
		else
		{
			printf("Agmal Ayo Bangun disabled 10s\n");
			call_iraj=1;
			count_iraj=0;
		}
	}
	message[0]='\0';
    }
    return 0;
}
