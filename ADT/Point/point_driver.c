#include "point.h"
/* Program driver ADT Point */
int main(){
	POINT p1, p2;
	float deltaX, deltaY, sudutPutar;

	/* Pemanggilan MakePOINT, BacaPOINT */
	printf("masukan absis dan ordinat point 1 : ");
	BacaPOINT(&p1);
	printf("masukan absis dan ordinat point 2 : ");
	BacaPOINT(&p2);

	/* Pemanggilan EQ, NEQ */
	if(EQ(p1,p2)){
		printf("point 1 sama dengan point 2\n");
	} else if(NEQ(p1,p2)){
		printf("point 1 tidak sama dengan point 2\n");
	}

	/* Pemanggilan IsOrigin, IsOnSbX, IsOnSbY, Kuadran*/
	if(IsOrigin(p1)){
		printf("point 1 berada di titik 0,0\n");
	} else if(IsOnSbX(p1)){
		printf("point 1 berada pada sumbu x\n");
	} else if(IsOnSbY(p1)){
		printf("point 1 berada pada sumbu y\n");
	}
	if(!IsOrigin(p1) && !IsOnSbY(p1) && !IsOnSbX(p1)){
		printf("point 1 berada pada kuadran %d\n", Kuadran(p1));
	}

	/* Pemanggilan NextX, NextY, PlusDelta, MirrorOf, TulisPOINT */
	printf("Absis p2 ditambah 1 : ");
	p2 = NextX(p2);
	TulisPOINT(p2);

	printf("\nOrdinat p2 ditambah 1 : ");
	p2 = NextY(p2);
	TulisPOINT(p2);

	printf("\nMasukan delta x dan delta y : ");
	scanf("%f %f", &deltaX, &deltaY);
	printf("p2 ditambah sebesar (delta x, delta y) : ");
	p2 = PlusDelta(p2, deltaX, deltaY);
	TulisPOINT(p2);

	printf("\np2 dicerminkan ke sumbu x : ");
	p2 = MirrorOf(p2, true);
	TulisPOINT(p2);
	printf("\np2 dicerminkan ke sumbu y : ");
	p2 = MirrorOf(p2, false);
	TulisPOINT(p2);

	/* Pemanggilan Jarak0, Panjang, Geser, GeserKeSbX, GeserKeSbY, Mirror, Putar */
	printf("\n\nJarak p1 ke titik (0,0) : %f\n", Jarak0(p1));
	printf("Jarak antara p1 dan p2 : %f\n", Panjang(p1,p2));

	printf("\n--- Menggeser titik p1 menggunakan prosedur Geser ---");
	printf("\nMasukan delta x dan delta y : ");
	scanf("%f %f", &deltaX, &deltaY);
	printf("p1 ditambah sebesar (delta x, delta y) : ");
	Geser(&p1, deltaX, deltaY);
	TulisPOINT(p1);

	printf("\np1 digeser ke sumbu x : ");
	GeserKeSbX(&p1);
	TulisPOINT(p1);

	printf("\np1 digeser ke sumbu y : ");
	GeserKeSbY(&p1);
	TulisPOINT(p1);

	printf("\np2 dicerminkan terhadap sumbu x : ");
	Mirror(&p2, true);
	TulisPOINT(p2);
	printf("\np2 dicerminkan terhadap sumbu y : ");
	Mirror(&p2, false);
	TulisPOINT(p2);

	printf("\n\nMasukan sudut derajat putar : ");
	scanf("%f", &sudutPutar);
	Putar(&p2, sudutPutar);
	printf("p2 diputar sebesar %f derajat : ", sudutPutar);
	TulisPOINT(p2);

	return 0;
}