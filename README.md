# SoalShift_modul3_A08
Penjelasan soalshift modul 3

## Soal 1
Buatlah program C yang bisa menghitung faktorial secara parallel lalu menampilkan hasilnya secara berurutan
Contoh:
    ./faktorial 5 3 4
    3! = 6
    4! = 24
    5! = 120
    
    
- Deklarasi variabel dan thread serta mengambil input
  argc : berfungsi untuk menghitung jumlah input
  args : berfungsi untuk menyimpan input
```c
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>

void* fact(void *args);

int main(int argc, char *args[]){
	char* temp;
	pthread_t thread[argc-1];
```

- Menggunakan bubble sort untuk mengurutkan input
```c
	for(int i=1;i<argc-1;i++){
		for(int j=0;j<(argc-i-1);j++){
		if(strcmp(args[j+1],args[j+2])<0){
			temp=args[j+1];
			args[j+1]=args[j+2];
			args[j+2]=temp;
		}
		}
	}
	
```

- Menggunakan thread untuk menghitung tiap angka dan join agar menunggu hingga child thread yang diinginkan selesai di eksekusi.
```c

	for(int i=0;i<argc-1;i++){
		pthread_create(&(thread[i]),NULL,&fact,(void*)args[i+1]);
	}

	for(int i=0;i<argc-1;i++){
		pthread_join(thread[i],NULL);
	}
}
```

- Fungsi untuk menghitung factorial
```c
void* fact(void *args){
	int a;
    a=strtol((char*)args,NULL,10);
	int result=1;
    for(int i=1;i<=a;i++){
	    result*=i;
    }
	printf("%d! = %d\n",a,result);
}
```


## Soal 2
Pada suatu hari ada orang yang ingin berjualan 1 jenis barang secara private, dia memintamu membuat program C dengan spesifikasi sebagai berikut:
Terdapat 2 server: server penjual dan server pembeli
1 server hanya bisa terkoneksi dengan 1 client
2 Server penjual dan server pembeli memiliki stok barang yang selalu sama
3 Client yang terkoneksi ke server penjual hanya bisa menambah stok
4 Cara menambah stok: client yang terkoneksi ke server penjual mengirim string “tambah” ke server lalu stok bertambah 1
5 Client yang terkoneksi ke server pembeli hanya bisa mengurangi stok
6 Cara mengurangi stok: client yang terkoneksi ke server pembeli mengirim string “beli” ke server lalu stok berkurang 1
7 Server pembeli akan mengirimkan info ke client yang terhubung dengannya apakah transaksi berhasil atau tidak berdasarkan ketersediaan stok
  Jika stok habis maka client yang terkoneksi ke server pembeli akan mencetak “transaksi gagal”
  Jika stok masih ada maka client yang terkoneksi ke server pembeli akan mencetak “transaksi berhasil”
8 Server penjual akan mencetak stok saat ini setiap 5 detik sekali
Menggunakan thread, socket, shared memory


##### Client Pembeli 
  - Mengambil Inputan dan mengirimnya ke server.
  - Menerima dari server kemudian di tampilkan.
  - Mengosongkan memori variabel `buffer`.
    
    ```c
    char beli[10];

    while(1){

        scanf("%s",beli);
        send(sock , beli , strlen(beli) , 0 );

        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );

        memset(buffer,0,sizeof(buffer));
    }
    return 0;
    }
    ```

##### Client Penjual

- Input tambah.
- Mengirim Inputan ke server.
- menerima dari server kemudian di tampilkan.
- mengosongkan memori variabel `buffer`.


```c
    char tambah[10];

    while(1){
        scanf("%s",tambah);
        send(sock , tambah , strlen(tambah) , 0 );
        valread = read( sock , buffer, 1024);
        printf("%s\n",buffer );
        memset(buffer,0,sizeof(buffer));
        
    }
    return 0;
}
```

##### Server Pembeli

- Membuat Shared Memory dengan Server Penjual untuk `jumlah_barang`

```c
    key_t key = 1234;
    int *jumlah_barang;

    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumlah_barang = shmat(shmid, NULL, 0);

    *jumlah_barang = 1;
```

- Menampilkan jumlah barang.
- Menerima inputan dari client.
- Membandingkan inputan dengan string 'beli'.
- Jika sama dan jika jumlah barang lebih dari nol jumlah barang dikurang.
- Kemudian mengirim string yang disimpan di `membeli`.
- Jika jumlah sama dengan atau kurang dari 0 maka mengirim string yg disimpan di `habis`.

```c

    }
    while(1){
        printf("%d\n", *jumlah_barang);
        valread = read( new_socket , buffer, 1024);
        printf("%s\n",buffer );
        if(strcmp(buffer,"beli")==0){
            if(*jumlah_barang > 0){
                *jumlah_barang = *jumlah_barang -1;
                send(new_socket , membeli, strlen(membeli),0);
            }
            else {
                send(new_socket, habis, strlen(habis),0);
            }
        }

    }
    return 0;
}
```

##### Server Penjual
- Thread untuk menapilkan jumlah barang tiap 5 detik sekali

```c
void* count(void* ptr){
    int num;
    while(1){
        num = *jumlah_barang;
        printf("Jumlah Barang sekarang : %d \n", num );
        sleep(5);
    }
}
```

- Membuat Shared Memory 

```c
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    jumlah_barang = shmat(shmid, NULL, 0);

*jumlah_barang = 1;
```
- Menjalankan thread `count`
```c
int th = pthread_create(&(tid[1]),NULL,count,NULL);
```
- Menerima inputan dari client.
- Membandingkan inputan dengan string 'tambah'.
- Jika sama dan jika jumlah barang lebih dari nol jumlah barang ditambah 1.
- Kemudian mengirim string ke client yang disimpan di `menambah`.
- Jika string yang dikirim salah akan menampilkan pesan salah. 
 
```c
    while(1){

        valread = read( new_socket , buffer, 1024);

        if (strcmp(buffer,"tambah")==0){
            *jumlah_barang = *jumlah_barang + 1;
            send(new_socket , menambah , strlen(menambah) , 0 );
            
        }
        else {
            send(new_socket , salah , strlen(salah) , 0 );
        }
    }
return 0;
```

## Soal 3
1. Disini digunakan 4 thread yaitu sebagai berikut

a. untuk mengecek status Agmal ketika sudah terpanggil 3 kali dan mendisable Iraj selama 10 detik jika Iraj terpanggil

b. untuk mengecek status Iraj ketika sudah terpanggil 3 kali dan mendisable Agmal selama 10 detik jika Agmal terpanggil

c. untuk menambahkan status wakeup Agmal sebanyak 15 point, dan memeriksa jika sudah mencapai lebih dari sama dengan 100, akan muncul pesan "Agmal terbangun, mereka bangun pagi dan berolahraga"

d. untuk mengurangi status spirit Agmal sebanyak 20 point, dan memeriksa jika sudah mencapai kurang dari sama dengan 0, akan muncul pesan "Iraj ikut tidur, dan bangun kesiangan bersama Agmal"
```
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
```
2. di fungsi main berisi status wakeup dan status spirit awal, jika diantara kedua tersebut dipanggil, maka akan ada perubahan nilai (tambah atau kurang), jika diantara kedua panggilan dipanggil sebanyak 3 kali, maka Agmal atau Iraj bakal berhenti selama 10 detik
```
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
```

## Soal 4
1. Disini digunakan 4 thread dalam menjalankan program ini, 2 thread pertama digunakan untuk membuat file directory FolderProses dan membuat text berisi laporan status proses, dan kedua thread tersebut harus dijalankan secara bersamaan.

1a. Untuk membuat FolderProses1 (folder) dan SimpanProses1.txt (file proses)

1b. Untuk membuat FoderProses2 dan simpanProses2.txt
```
void* proses1(){
	system("mkdir -p ~/Documents/FolderProses1");
	system("ps -aux|head -10>>~/Documents/FolderProses1/SimpanProses1.txt");
}

void* proses2(){
	system("mkdir -p ~/Documents/FolderProses2");
	system("ps -aux|head -10>>~/Documents/FolderProses2/SimpanProses2.txt");
}
```

2. 2 thread berikutnya digunakan untuk membuat zip dan ekstrak zip tersebut, kedua thread tersebut dilakukan secara bersamaan.

2a. Untuk zip file SimpanProses1.txt menjadi KompresProses1.zip dan mengestrak kembali menjadi SimpanProses1.txt di dalam folder Documents

2b. Untuk zip file SimpanProses2.txt menjadi KompresProses2.zip dan mengestrak kembali menjadi SimpanProses2.txt di dalam folder Documents
```
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
```

3. Untuk fungsi main, hanya multithread dari thread yg dibuat untuk mendukung program ini
```
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
```
## Soal 5

Masih belum ada deskripsi, karena revisi
