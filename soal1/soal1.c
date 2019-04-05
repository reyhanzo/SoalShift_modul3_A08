#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* fact(void *args);

int main(int argc, char *args[]){
	char* temp;
	pthread_t thread[argc-1];

	for(int i=1;i<argc-1;i++){
		for(int j=0;j<(argc-i-1);j++){
		if(strcmp(args[j+1],args[j+2])<0){
			temp=args[j+1];
			args[j+1]=args[j+2];
			args[j+2]=temp;
		}
		}
	}

	for(int i=0;i<argc-1;i++){
		pthread_create(&(thread[i]),NULL,&fact,(void*)args[i+1]);
	}

	for(int i=0;i<argc-1;i++){
		pthread_join(thread[i],NULL);
	}
}

void* fact(void *args){
	int a;
    a=strtol((char*)args,NULL,10);
	int result=1;

    for(int i=1;i<=a;i++){
	    result*=i;
    }
	printf("%d! = %d\n",a,result);

}
