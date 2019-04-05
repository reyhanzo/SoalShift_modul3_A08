#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

pthread_t tid[6]; //inisialisasi array untuk menampung thread dalam kasus ini ada 2 thread
int hunger_status=200;
int hygiene_status=100;
int health_status=300;
int enemy_health_status=100;
int food_status=10;
int bath_status=0;
int standb=1;

int getchent (void)
{
	int c = 0;
	static struct termios oldTermios, newTermios;

	tcgetattr(STDIN_FILENO, &oldTermios);
	newTermios = oldTermios;

	cfmakeraw(&newTermios);

	tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);
	c = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);

	switch (c) {
	   case 113: // q
	   printf("\n\n");
           exit(0);
           break;
    	case 105: // i
        printf("insert\n");
        	break;
    	default:
        	break;
}

void *hungry(void *arg)
{
	int i = 99999;
	while(i--)
	{
		if(standb==1)
		{
		sleep(10);
		hunger_status-=5;
		}
	}
}

void *dirty(void *arg)
{
	int i = 99999;
	while(i--)
	{
		if(standb==1)
		{
		sleep(30);
		hygiene_status-=30
		}
	}
}

void *regen(void *arg)
{
	int i = 99999;
	while(i--)
	{
		if(battle==1){}
		else{
		sleep(10);
		health_status+=5;
		}
	}
}

void *timer(void *arg)
{
	int i = 99999;
	while(i--)
	{
		if(standb==1){
		if(counter>0){
		sleep(1);
		counter--;
		}
	   }
	}

}

void battle(void *arg)
{
	char choosebattle;
	while(1)
	{
		if(enemy_health_status<=0)
		{
			printf("%s DEFEATED ENEMY \n", name);
			printf("-----------VICTORY--------- \n");
			standb=1;
			sleep(2);
			system("clear");
			break;
		}
		if(health_status<=0)
		{
			printf("%s DEFEATED \n", name);
			printf("GO HOME, %s HEALTH IS EMPTY\n", name);
			standb=1;
			sehat=0;
			sleep(2);
			system("clear");
			break;
		}
		printf("Battle Mode\n");
		printf("%s Health : %d\n", name, health_status);
		printf("Enemy’s Health : %d\n", enemy_health_status);
		printf("Choices\n");
		printf("1. Attack\n");
		printf("2. Run\n");
		pilih_b=getchent();
		if(choosebattle=='1')
		{
			system("clear");
			health_status-=20;
			enemy_health_status-=20;
			printf("%s Attacks the Enemy !!!\n", name);
			printf("Enemy Health -20 ! \n");
			printf("Enemy Attacks %s !!!\n", name);
			printf("%s Health -20 ! \n", name);
			sleep(5);
			system("clear");
		}
		if(pilih_b=='2')
		{
			system("clear");
			printf("%s is Running \n", name);
			printf("%s escaped the battle\n", name);
			standb=1;
			sleep(3);
			system("clear");
			break;
		}
	}
}

void shop(void *arg)
{
		int choose4;	
		printf("Shop Mode");
		printf("Shop food stock : %d\n", shop_stock);
		printf("Your food stock : %d\n", food_status);
		printf("1. Buy\n 2.Back\n");
		scanf("%d\n", choose4);
		if(choose4=='1')
		{
			
		}

		else if(choose4=='2')
		{
			
		}
}


void stand(void *arg)
{
	while(1)
{
	system("clear");
	char name[10]
	int choose;
	printf("Standby Mode");
	printf("Health = %d\n", health_status);
	printf("Hunger = %d\n", hunger_status);
	printf("Hygiene = %d\n", hygiene_status);
	printf("Food left = %d\n", food_status);
	printf("1. Eat\n 2.Bath\n 3.Battle\n 4.Shop\n 5.Exit\n");
	scanf("%d\n", choose);

	if(choose=='1')
	{
		
	}

	else if(choose=='2')
	{
		
	}

	else if(choose=='3')
	{
		
	}

	else if(choose=='4')
	{
		
	}

	else if(choose=='5')
	{
		
	}

	else
	{
		printf("Try Again");
	}

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	exit(0);
	return 0;
}
