#include "mesinkata.h"
#include <stdio.h>

/*NIM : 13516089*/
/*Nama : Priagung Satyagama*/

boolean isKataSama(Kata K1, Kata K2){
	if(K1.Length == K2.Length){
		for(int i=1; i<=K1.Length; i++){
			if(K1.TabKata[i] != K2.TabKata[i]){
				return false;
			}
		}
		return true;
	}
	else return false;
}

int main(){
	Kata TITIK, KOMA, Pesan[10000];
	TITIK.Length = 5;
	TITIK.TabKata[1] = 'T';
	TITIK.TabKata[2] = 'I';
	TITIK.TabKata[3] = 'T';
	TITIK.TabKata[4] = 'I';
	TITIK.TabKata[5] = 'K';

	KOMA.Length = 4;
	KOMA.TabKata[1] = 'K';
	KOMA.TabKata[2] = 'O';
	KOMA.TabKata[3] = 'M';
	KOMA.TabKata[4] = 'A';

	STARTKATA();
	int i=0;
	if(CC != MARK){
		Pesan[i] = CKata;
		i++;
	}
	while(CC != MARK){
		ADVKATA();
		Pesan[i] = CKata;
		i++;
	}
	/*for(int k=1; k<=Pesan[i-1].Length; k++){
		printf("%c", Pesan[i-1].TabKata[k]);
	}
	printf("\n");*/

	int jmlReg=0, jmlPjg=0;
	long harga;
	for(int j=0; j<i; j++){
		if(isKataSama(Pesan[j], KOMA)){
			printf(","); 
		}
		else if(isKataSama(Pesan[j], TITIK)){
			printf(".");
		}
		else{
			if(j!=0)
				printf(" ");
			for(int k=1; k<=Pesan[j].Length; k++){
				printf("%c", Pesan[j].TabKata[k]);
			}
			if(Pesan[j].Length<10){
				jmlReg++;
			}
			else {
				jmlPjg++;
			}
		}
	}

	printf("\n%d\n%d\n", jmlReg, jmlPjg);
	if(i>10){
		harga = 1000*jmlReg + 1500*jmlPjg;
		harga = harga - harga/10;
	}
	else{
		harga = 1000*jmlReg + 1500*jmlPjg;
	}
	printf("%d\n", harga);
}