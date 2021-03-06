#include "matriks.h"
#include <stdio.h>

/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j)
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
{
	boolean b1,b2;
	b1 = (i>=BrsMin) && (i<=BrsMax);
	b2 = (j>=KolMin) && (j<=KolMax);
	return b1&&b2;
}

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terkecil M */
{
	return BrsMin;
}

indeks GetFirstIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terkecil M */
{
	return KolMin;
}

indeks GetLastIdxBrs (MATRIKS M)
/* Mengirimkan indeks baris terbesar M */
{
	return NBrsEff(M);
}

indeks GetLastIdxKol (MATRIKS M)
/* Mengirimkan indeks kolom terbesar M */
{
	return NKolEff(M);
}

boolean IsIdxEff (MATRIKS M, indeks i, indeks j)
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
{
	boolean ieff,jeff;
	ieff = i>=BrsMin && i<=GetLastIdxBrs(M);
	jeff = j>=KolMin && j<=GetLastIdxKol(M);
	return ieff && jeff;
}

ElType GetElmtDiagonal (MATRIKS M, indeks i)
/* Mengirimkan elemen M(i,i) */
{
	return Elmt(M,i,i);
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl)
/* Melakukan assignment MHsl  MIn */
{
	indeks i,j;
	MakeMATRIKS(NBrsEff(MIn), NKolEff(MIn), MHsl);
	for(i=GetFirstIdxBrs(*MHsl); i<=GetLastIdxBrs(*MHsl); i++){
		for(j=GetFirstIdxKol(*MHsl); j<=GetLastIdxKol(*MHsl); j++){
			Elmt(*MHsl, i, j) = Elmt(MIn, i, j);
		}
	}
}

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK)
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
{
	indeks i,j;

	MakeMATRIKS(NB,NK,M);
	for(i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
		for(j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
			scanf("%d", &Elmt(*M, i, j));
		}
	}
}

void TulisMATRIKS (MATRIKS M)
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
{
	indeks i,j;

	for(i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
		j=GetFirstIdxKol(M);
		printf("%d", Elmt(M,i,j));
		for(j=GetFirstIdxKol(M)+1; j<=GetLastIdxKol(M); j++){
			printf(" %d", Elmt(M,i,j));
		}
		if(i<GetLastIdxBrs(M)){
			printf("\n");
		}
	}
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */                                  
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++){
		for(j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++){
			Elmt(M1,i,j) = Elmt(M2,i,j) + Elmt(M1,i,j);
		}
	}

	return M1;
}

MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 – M2 */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++){
		for(j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++){
			Elmt(M1,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);
		}
	}

	return M1;
}

MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2)
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
{
	indeks i,j,k;
	MATRIKS M;

	MakeMATRIKS(NBrsEff(M1), NKolEff(M2), &M);

	for(i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
		for(j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
			Elmt(M,i,j) = 0;
			for(k=GetFirstIdxKol(M1); k<=GetLastIdxKol(M1); k++){
				Elmt(M,i,j) += Elmt(M1,i,k)*Elmt(M2,k,j);
			}
		}
	}

	return M;
}

MATRIKS KaliKons (MATRIKS M, ElType X)
/* Mengirim hasil perkalian setiap elemen M dengan X */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
		for(j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
			//mengalikan tiap elemen dengan X
			Elmt(M,i,j) *= X;
		}
	}

	return M;
}

void PKaliKons (MATRIKS * M, ElType K)
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
		for(j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
			//mengalikan tiap elemen dengan K
			Elmt(*M,i,j) *= K;
		}
	}
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2) 
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
{
	indeks i=GetFirstIdxBrs(M1),j;
	boolean equal = true, a, b;
	a = NBElmt(M1) == NBElmt(M2);
	b = GetFirstIdxBrs(M1) == GetFirstIdxBrs(M2) && GetLastIdxKol(M1) == GetLastIdxKol(M2);

	if(a&&b){
		while(i<=GetLastIdxBrs(M1) && equal){
			j=GetFirstIdxKol(M1);
			while(j<=GetLastIdxKol(M1) && equal){

				//mengecek kesamaan tiap elemen
				if(Elmt(M1,i,j) != Elmt(M2,i,j)){
					equal = false;
				}
				j++;
			}
			i++;
		}
	}
	else {
		equal = false;
	}

	return equal;
}

boolean NEQ (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika M1 tidak sama dengan M2 */
{
	return !EQ(M1,M2);
}

boolean EQSize (MATRIKS M1, MATRIKS M2)
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
{
	return (NBrsEff(M1) == NBrsEff(M2)) && (NKolEff(M1) == NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M)
/* Mengirimkan banyaknya elemen M */
{
	return NBrsEff(M)*NKolEff(M);
}
/* ********** KELOMPOK TEST TERHADAP MATRIKS ********** */
boolean IsBujurSangkar (MATRIKS M)
/* Mengirimkan true jika M adalah matriks dg ukuran baris dan kolom sama */
{
	return NBrsEff(M) == NKolEff(M);
}

boolean IsSimetri (MATRIKS M)
/* Mengirimkan true jika M adalah matriks simetri : IsBujurSangkar(M) 
   dan untuk setiap elemen M, M(i,j)=M(j,i) */
{
	indeks i=GetFirstIdxBrs(M),j;
	boolean simetri=true;
	if(!IsBujurSangkar(M)){
		simetri=false;
	}
	else {
		while(simetri && i<=GetLastIdxBrs(M)){
			j=GetFirstIdxKol(M);
			while(simetri && j<=GetLastIdxKol(M)){

				//mengecek kesimetrisan tiap elemen
				if(Elmt(M,i,j) != Elmt(M,j,i)){
					simetri=false;
				}
				j++;
			}
			i++;
		}
	}

	return simetri;
}

boolean IsSatuan (MATRIKS M)
/* Mengirimkan true jika M adalah matriks satuan: IsBujurSangkar(M) dan 
   setiap elemen diagonal M bernilai 1 dan elemen yang bukan diagonal bernilai 0 */ 
{
	int i=GetFirstIdxBrs(M),j;
	boolean satuan=true;

	if(!IsBujurSangkar(M)){
		satuan=false;
	}
	else {
		while(i<=GetLastIdxBrs(M) && satuan){
			j=GetFirstIdxKol(M);
			while(j<=GetLastIdxKol(M) && satuan){
				//pengecekan diagonal nya bernilai 1 atau tidak
				if(i==j && !Elmt(M,i,j)==1){
					satuan=false;
				}

				//pengecekan elemen lain, bernilai 0 atau tidak
				if(i!=j && !Elmt(M,i,j)==0){
					satuan=false;
				}
				j++;
			}
			i++;
		}
	}
	return satuan;
}

boolean IsSparse (MATRIKS M)
/* Mengirimkan true jika M adalah matriks sparse: mariks “jarang” dengan definisi: 
   hanya maksimal 5% dari memori matriks yang efektif bukan bernilai 0 */ 
{
	int count=0;
	indeks i,j;

	for(i=GetFirstIdxBrs(M);i<=GetLastIdxBrs(M);i++){
		for(j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
			if(Elmt(M,i,j) != 0){
				count++;
			}
		}
	}

	return (float)count/NBElmt(M) <= 0.05;
}

MATRIKS Inverse1 (MATRIKS M)
/* Menghasilkan salinan M dengan setiap elemen "di-invers", yaitu dinegasikan (dikalikan -1) */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
		for(j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
			Elmt(M,i,j) *= -1;
		}
	}

	return M;
}

float Determinan (MATRIKS M)
/* Prekondisi: IsBujurSangkar(M) */
/* Menghitung nilai determinan M */
{
	int i,j,k,Nb=NBrsEff(M),Nk=NKolEff(M),ib,ik;
	MATRIKS M1;
	float det=0;
	if(Nb==1 && Nk==1){
		det += Elmt(M,1,1);
	}
	else if(Nb==2 && Nk==2){
		det+=Elmt(M,1,1)*Elmt(M,2,2) - Elmt(M,1,2)*Elmt(M,2,1);
	} else {
		for(i=GetFirstIdxKol(M);i<=Nk;i++){
			MakeMATRIKS(Nb-1, Nk-1, &M1);
			ib=1;
			for(j=GetFirstIdxBrs(M);j<=Nb;j++){
				ik=1;
				for(k=GetFirstIdxKol(M); k<=Nk; k++){	
					if(j!=1 && k!=i){
						Elmt(M1,ib,ik) = Elmt(M,j,k);
						ik++;
					}
				}
				if(j!=1){
					ib++;
				}
			}
			if(i%2==1){
				det+=Elmt(M,1,i)*Determinan(M1);
			} else{
				det-=Elmt(M,1,i)*Determinan(M1);
			}
		}

	}
	return det;
}

void PInverse1 (MATRIKS * M)
/* I.S. M terdefinisi */
/* F.S. M di-invers, yaitu setiap elemennya dinegasikan (dikalikan -1) */
{
	indeks i,j;

	for(i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
		for(j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
			Elmt(*M,i,j) *= -1;
		}
	}
}

void Transpose (MATRIKS * M)
/* I.S. M terdefinisi dan IsBujursangkar(M) */
/* F.S. M "di-transpose", yaitu setiap elemen M(i,j) ditukar nilainya dengan elemen M(j,i) */
{
	indeks i,j;
	MATRIKS M1;
	MakeMATRIKS(NBrsEff(*M), NKolEff(*M), &M1);

	for(i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
		for(j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
			Elmt(M1,i,j) =  Elmt(*M,j,i);
		}
	}

	CopyMATRIKS(M1, M);
}