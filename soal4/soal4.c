#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>
pthread_t tid[10];

void* proses1(){
	system("mkdir -p ~/Documents/FolderProses1");
	system("ps -aux|head -10>>~/Documents/FolderProses1/SimpanProses1.txt");
}

void* proses2(){
	system("mkdir -p ~/Documents/FolderProses2");
	system("ps -aux|head -10>>~/Documents/FolderProses2/SimpanProses2.txt");
}

void* zip1(){
	system("zip -j ~/Documents/FolderProses1/KompresProses1.zip ~/Documents/FolderProses1/SimpanProses1.txt");
	system("rm ~/Documents/FolderProses1/SimpanProses1.txt");
	sleep(15);

		printf("Menunggu 15 detik untuk mengekstrak kembali\n");
		system("unzip ~/Documents/FolderProses1/KompresProses1.zip -d ~/Documents");
		system("rm ~/Documents/FolderProses1/KompresProses1.zip");
	
}

void* zip2(){
	system("zip -j ~/Documents/FolderProses2/KompresProses2.zip ~/Documents/FolderProses2/SimpanProses2.txt");
	system("rm ~/Documents/FolderProses2/SimpanProses2.txt");
	sleep(15);


		printf("Menunggu 15 detik untuk mengekstrak kembali\n");
		system("unzip ~/Documents/FolderProses2/KompresProses2.zip -d ~/Documents");
		system("rm ~/Documents/FolderProses2/KompresProses2.zip");
	
}

int main()
{
	pthread_create(&(tid[0]),NULL,&proses1,NULL);
	pthread_join(tid[0],NULL);
	pthread_create(&(tid[1]),NULL,&proses2,NULL);
	pthread_join(tid[1],NULL);
	pthread_create(&(tid[0]),NULL,&zip1,NULL);
	pthread_create(&(tid[1]),NULL,&zip2,NULL);
	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
}
