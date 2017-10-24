#include <stdio.h>
#include <stdlib.h>
#include "arraydinamik.h"

int main(){
	//KAMUS
	TabInt T1,T2;
	int c,idx,max,min;

	//membaca isi array dari user
	//v1
	printf("Pembacaan array versi input neff:\n");
	BacaIsi(&T1);
	//v2
	printf("Pembacaan array versi input nilai undef:\n");
	MakeEmpty(&T2,5);
	BacaIsiTab(&T2);

	//tulis isi tab
	printf("Penulisan array versi vertikal:\n");
	TulisIsi(T1);
	printf("Penulisan array versi horizontal:\n");
	TulisIsiTab(T2);
	printf("\n");

	//jumlah alokasi array
	printf("%d\n",MaxNbEl(T1));
	printf("%d\n",MaxNbEl(T2)); 

	//cek kesamaan
	if (IsEQ(T1,T2)){
		printf("array equal!\n");
	}
	else{
		printf("array tidak equal\n");
	}

	if(NbElmt(T1)==NbElmt(T2)){
		printf("array sama panjang dan bisa dioperasikan\n");
		//plustab
		printf("hasil PlusTab T1 dan T2:\n");
		TulisIsiTab(PlusTab(T1,T2));
		printf("\n");
		//minustab
		printf("hasil MinusTab T1 dan T2:\n");
		TulisIsiTab(MinusTab(T1,T2));
		printf("\n");
		//kalitab
		printf("hasil KaliTab T1 dan T2:\n");
		TulisIsiTab(KaliTab(T1,T2));
		printf("\n");	
	}
	else{
		printf("array tidak sama panjang(tidak ada +-*)\n");
	}
	//kalikons
	printf("input nilai konstanta yang akan dikali ke tab 1:\n");
	scanf("%d",&c);
	printf("hasil KaliTab T1 dengan konstanta %d: \n",c);
	TulisIsiTab(KaliKons(T1,c));
	printf("\n");

	//isless
	if(IsLess(T1,T2)){
		printf("T1 lebih kecil dari T2\n");
	}
	else{
		printf("T1 lebih besar dari T2\n");
	}

	//Searching
	//v1
	printf("input nilai yang akan dicari di T1:\n");
	scanf("%d",&c);
	if(SearchB(T1,c)){
		printf("Konstanta %d ada idx:%d di T1\n",c,Search1(T1,c));
	}
	else{
		printf("Konstanta tidak ada di T1\n");
	}
	if(SearchB(T2,c)){
		printf("Konstanta %d ada di idx:%d di T2\n",c,Search1(T2,c));
	}
	else{
		printf("Konstanta tidak ada di T2\n");
	}

	//maksimum minimum
	printf("Nilai maksimum T1 %d ada di idx:%d\n",ValMax(T1),IdxMaxTab(T1));
	printf("Nilai minimum T1 %d ada di idx:%d\n",ValMin(T1),IdxMinTab(T1));
	printf("Nilai maksimum T2 %d ada di idx:%d\n",ValMax(T2),IdxMaxTab(T2));
	printf("Nilai minimum T2 %d ada di idx:%d\n",ValMin(T2),IdxMinTab(T2));

	//InverseTab
	printf("InverseTab T1:\n");
	TulisIsiTab(InverseTab(T1));
	printf("\n");

	//IsSimetris
	if(IsSimetris(T1)){
		printf("T1 simetris\n");
	}
	else{
		printf("T1 tidak simetris\n");
	}


	//adding and deleting element
	//adding
	if(!IsFull(T2)){
		printf("input element yang akan ditambah ke tab 2:\n");
		scanf("%d",&c);
		AddAsLastEl(&T2,c);
		printf("input indeks untuk penambahan elemen ke tab 2:\n");
		scanf("%d",&idx);
		AddEli(&T2,c,idx);
		printf("input element unik yang akan ditambah ke tab 2:\n");
		scanf("%d",&c);
		AddElUnik(&T2,c);
		TulisIsiTab(T2);
		printf("\n");
	}
	else{
		printf("array penuh dan tidak bisa ditambah element\n");
	}

	//deleting
	if(!IsEmpty(T1)){
		printf("input element yang akan dihapus dari tab 1:\n");
		scanf("%d",&c);
		DelLastEl(&T1,&c);
		printf("input indeks untuk penghapusan elemen tab 1:\n");
		scanf("%d",&idx);
		DelEli(&T1,idx,&c);
		TulisIsiTab(T1);
		printf("\n");
	}

	//Sorting
	printf("T1 dan T2 akan diurutkan, dengan T2 ascending dan T1 descending\n");
	InsSortAsc(&T2);
	MaxSortDesc(&T1);
	TulisIsiTab(T1);
	printf("\n");
	TulisIsiTab(T2);
	printf("\n");

	//tabel dengan elemen urut untuk tab 2
	//searching
	SearchUrut(T2,c);
	//maxmin urut
	MaxMinUrut(T2,&max,&min);
	printf("nilai maksimum T2 urut: %d\n",max);
	printf("nilai minimum T2 urut: %d\n",min);
	//Adding and deleting
	printf("input element yang akan ditambah ke tab 2(urut):\n");
	scanf("%d",&c);
	Add1Urut(&T2,c);
	TulisIsiTab(T2);
	printf("\n");
	printf("input element yang akan dihapus dari tab 2(urut):\n");
	scanf("%d",&c);
	Del1Urut(&T2,c);
	TulisIsiTab(T2);
	printf("\n");

	return 0;
}