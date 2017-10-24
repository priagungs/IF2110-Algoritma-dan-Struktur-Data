#include "jam.h"
#include <stdio.h>
/*Driver ADT Jam*/
int main(){
	JAM jam1, jam2;
	int optionJam, option1, NDetik;

	printf("Masukan jam pertama dengan format HH MM SS :\n");

	BacaJAM(&jam1); //pengetesan IsJAMValid, MakeJAM, BacaJAM
	printf("Masukan jam kedua dengan format HH MM SS :\n");
	BacaJAM(&jam2); //pengetesan IsJAMValid, MakeJAM, BacaJAM

	/*pengetesan JEQ, JNEQ, JLT, JGT*/
	if(JEQ(jam1, jam2)){
		printf("jam pertama dan jam kedua adalah sama\n");
	} else if(JNEQ(jam1, jam2)){
		if(JLT(jam1,jam2)){
			printf("jam pertama lebih kecil dari jam kedua\n");
		} else if(JGT(jam1, jam2)){
			printf("jam pertama lebih besar dari jam kedua\n");
		}
	}

	/*pengetesan NextDetik, NextNDetik, PrevDetik, PrevNDetik*/
	printf("ketik 1 untuk manipulasi jam pertama, \nketik 2 untuk manipulasi jam kedua: ");
	scanf("%d", &optionJam);
	if(optionJam==1)
		/*memanipulasi jam pertama*/
	{
		printf("ketik angka : \n1. Menambah 1 detik\n2. Menambah N detik\n3. Mengurangi 1 detik\n4. Mengurangi N detik\n");
		scanf("%d", &option1);
		if(option1==1){
			jam1 = NextDetik(jam1);
		} else if(option1==2){
			printf("masukan jumlah detik yg akan ditambahkan: ");
			scanf("%d", &NDetik);
			jam1 = NextNDetik(jam1, NDetik);
		} else if(option1==3){
			jam1 = PrevDetik(jam1);
		} else if(option1==4){
			printf("masukan jumlah detik yg akan dikurangi: ");
			scanf("%d", &NDetik);
			jam1 = PrevNDetik(jam1, NDetik);
		}
	} else if(optionJam == 2)
		/*memanipulasi jam kedua*/
	{
		printf("ketik angka : 1. Menambah 1 detik\n2. Menambah N detik\n3. Mengurangi 1 detik\n4. Mengurangi N detik\n");
		scanf("%d", &option1);
		if(option1==1){
			jam2 = NextDetik(jam2);
		} else if(option1==2){
			printf("masukan jumlah detik yg akan ditambahkan: ");
			scanf("%d", &NDetik);
			jam2 = NextNDetik(jam2, NDetik);
		} else if(option1==3){
			jam2 = PrevDetik(jam2);
		} else if(option1==4){
			printf("masukan jumlah detik yg akan dikurangi: ");
			scanf("%d", &NDetik);
			jam2 = PrevNDetik(jam2, NDetik);
		}
	}

	/*Pengetesan TulisJAM, Durasi*/
	printf("Jam pertama adalah :\n");
	TulisJAM(jam1);
	printf("\nJam kedua adalah :\n");
	TulisJAM(jam2);
	printf("\nDurasi antara jam pertama dan jam kedua adalah : %ld\n", Durasi(jam1, jam2));
	
	return 0;
}