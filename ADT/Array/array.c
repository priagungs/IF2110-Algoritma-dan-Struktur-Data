#include "array.h"
#include <stdio.h>

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T)
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
{
  Neff(*T)=0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T)
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
{
  return Neff(T);
}

/* *** Daya tampung container *** */
int MaxNbEl (TabInt T)
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
{
  return IdxMax;
}

/* *** Selektor INDEKS *** */
IdxType GetFirstIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
{
  return IdxMin;
}

IdxType GetLastIdx (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
{
  return Neff(T)+IdxMin-1;
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
{
  return (IdxMin <= i) && (IdxMax >= i);
}
boolean IsIdxEff (TabInt T, IdxType i)
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
{
  return (GetFirstIdx(T) <= i) && (GetLastIdx(T) >= i); 
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T)
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
{
  return Neff(T) == 0;
}

/* *** Test tabel penuh *** */
boolean IsFull (TabInt T)
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
{
  return Neff(T) == IdxMax-IdxMin+1;
}
/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
{
  int N, i;
  scanf("%d", &N);
  while(N>MaxNbEl(*T) || N<0){
    scanf("%d", &N);    
  }
  if(N==0){
    MakeEmpty(T);
  } 
  else{
    for(i=IdxMin;i<=N;i++){
      scanf("%d", &Elmt(*T, i));
    }
  }
  Neff(*T)=N;
}

void BacaIsiTab (TabInt * T)
/* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca elemen T sampai dimasukkan nilai -9999 */
/* Dibaca elemen satu per satu dan disimpan mulai dari IdxMin */
/* Pembacaan dihentikan jika pengguna memasukkan nilai -9999 */
/* Jika dari pertama dimasukkan nilai -9999 maka terbentuk T kosong */
{
  ElType x;
  Neff(*T)=0;
  scanf("%d",&x);
  while(x != -9999 && !IsFull(*T)){
    Neff(*T)++;
    Elmt(*T, Neff(*T)) = x;
    scanf("%d",&x);
  }
}

void TulisIsi (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong : indeks dan elemen tabel ditulis berderet ke bawah */
/*      Jika T kosong : Hanya menulis "Tabel kosong" */
/* Contoh: Jika isi Tabel: [1, 20, 30, 50]
   Maka tercetak di layar:
   [1]1
   [2]20
   [3]30
   [4]50
*/
{
  int i;
  if(IsEmpty(T)){
    printf("Tabel kosong\n");
  } 
  else {
    for(i=GetFirstIdx(T); i<=GetLastIdx(T); i++){
      printf("[%d]%d\n", i, Elmt(T,i));
    }
  }
}

void TulisIsiTab (TabInt T)
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
{
  int i;
  if(IsEmpty(T)){
    printf("[]");
  } 
  else {
    printf("[%d", Elmt(T, GetFirstIdx(T)));
    for(i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++){
      printf(",%d", Elmt(T,i));
    }
    printf("]");
  }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
{
  TabInt THasil;
  int i;
  for(i=GetFirstIdx(T1); i<=GetLastIdx(T1); i++){
    Elmt(THasil, i) = Elmt(T1, i) + Elmt(T2, i);
  }
  Neff(THasil) = Neff(T1);

  return THasil;
}

TabInt MinusTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
{
  TabInt THasil;
  int i;
  for(i=GetFirstIdx(T1); i<=GetLastIdx(T1); i++){
    Elmt(THasil, i) = Elmt(T1, i) - Elmt(T2, i);
  }
  Neff(THasil) = Neff(T1);

  return THasil;
}

TabInt KaliTab (TabInt T1, TabInt T2)
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Mengirimkan T1 * T2 dengan definisi setiap elemen dengan indeks yang sama dikalikan */
{
  TabInt THasil;
  int i;
  for(i=GetFirstIdx(T1); i<=GetLastIdx(T1); i++){
    Elmt(THasil, i) = Elmt(T1, i) * Elmt(T2, i);
  }
  Neff(THasil) = Neff(T1);

  return THasil;
}


TabInt KaliKons (TabInt Tin, ElType c)
/* Prekondisi : Tin tidak kosong */
/* Mengirimkan tabel dengan setiap elemen Tin dikalikan c */
{
  int i;
  for(i=GetFirstIdx(Tin); i<=GetLastIdx(Tin); i++){
    Elmt(Tin, i) *= c;
  }
  return Tin;
}

/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
{
  boolean b = true;
  int i = GetFirstIdx(T1);
  if(NbElmt(T1) == NbElmt(T2)){
    while(i<=GetLastIdx(T1) && b){
      if(Elmt(T1, i) != Elmt(T2, i)){
        b = false;
      }
      i++;
    }
  } 
  else {
    b = false;
  }
  return b;
}

boolean IsLess (TabInt T1, TabInt T2)
/* Mengirimkan true jika T1 < T2, */
/* yaitu : sesuai dg analogi 'Ali' < Badu'; maka [0, 1] < [2, 3] */
{
 int i;

 if(IsEQ(T1,T2)){
  return false;
 }
 else {
  for(i=GetFirstIdx(T1); i<=GetLastIdx(T1); i++){
    if(Elmt(T1,i)>Elmt(T2,i)){
      return false;
    }
    else if(Elmt(T1,i) < Elmt(T2,i)){
      return true;
    }
  }
 }
 if(Neff(T1)>Neff(T2)){
  return false;
 } else{
  return true;
 }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search TANPA boolean */
{
  IdxType i=GetFirstIdx(T);
  if(IsEmpty(T)){
    return IdxUndef;
  } 
  else {

    while(i<=GetLastIdx(T) && Elmt(T,i)!=X){
      i++;
    }

    if(i>GetLastIdx(T)){
      return IdxUndef;
    } 
    else {
      return i;
    }

  }
}

IdxType Search2 (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Memakai skema search DENGAN boolean Found */
{
  boolean found=false;
  int i=GetFirstIdx(T);

  if(IsEmpty(T)){
    return IdxUndef;
  } 
  else {
    while(i<=GetLastIdx(T) && !found){
      if(Elmt(T,i)==X){
        found=true;
      }
      i++;
    }

    if(found){
      return i-1;
    } 
    else {
      return IdxUndef;
    }
  }
}

boolean SearchB (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Memakai Skema search DENGAN boolean */
{
  boolean found=false;
  int i=GetFirstIdx(T);

  while(!found && i<=GetLastIdx(T)){
    if(Elmt(T,i)==X){
      found=true;
    }
    i++;
  }

  return found;
}

boolean SearchSentinel (TabInt T, ElType X)
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* dengan metoda sequential search dengan sentinel */
/* Untuk sentinel, manfaatkan indeks ke-0 dalam definisi array dalam Bahasa C 
   yang tidak dipakai dalam definisi tabel */
{
  int i=GetLastIdx(T);
  Elmt(T, IdxMin-1) = X;
  while(Elmt(T,i)!=X){
    i--;
  }

  if(i<GetFirstIdx(T)){
    return false;
  }
  else {
    return true;
  }
}

/* ********** NILAI EKSTREM ********** */
ElType ValMax (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai maksimum tabel */
{
  int i, max = Elmt(T, GetFirstIdx(T));

  for(i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++){
    if(Elmt(T,i)>max){
      max = Elmt(T,i);
    }
  }

  return max;
}

ElType ValMin (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan nilai minimum tabel */
/* *** Mengirimkan indeks elemen bernilai ekstrem *** */
{
  int i, min = Elmt(T, GetFirstIdx(T));

  for(i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++){
    if(Elmt(T,i)<min){
      min = Elmt(T,i);
    }
  }

  return min;
}

IdxType IdxMaxTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai maksimum pada tabel */
{
  int i, max=Elmt(T, GetFirstIdx(T)), idx=GetFirstIdx(T);

  for(i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++){
    if(Elmt(T,i)>max){
      max = Elmt(T,i);
      idx=i;
    }
  }

  return idx;
}

IdxType IdxMinTab (TabInt T)
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks i terkecil dengan nilai elemen merupakan nilai minimum pada tabel */
{
  int i, min=Elmt(T, GetFirstIdx(T)), idx=GetFirstIdx(T);

  for(i=GetFirstIdx(T)+1; i<=GetLastIdx(T); i++){
    if(Elmt(T,i)<min){
      min = Elmt(T,i);
      idx=i;
    }
  }

  return idx;
}

/* ********** OPERASI LAIN ********** */
void CopyTab (TabInt Tin, TabInt * Tout)
/* I.S. Tin terdefinisi, Tout sembarang */
/* F.S. Tout berisi salinan dari Tin (elemen dan ukuran identik) */
/* Proses : Menyalin isi Tin ke Tout */
{
  int i;

  MakeEmpty(Tout);
  for(i=GetFirstIdx(Tin); i<=GetLastIdx(Tin); i++){
    Elmt(*Tout, i) = Elmt(Tin, i);
    Neff(*Tout)++;
  }
}

TabInt InverseTab (TabInt T)
/* Menghasilkan tabel dengan urutan tempat yang terbalik, yaitu : */
/* elemen pertama menjadi terakhir, */
/* elemen kedua menjadi elemen sebelum terakhir, dst.. */
/* Tabel kosong menghasilkan tabel kosong */
{
  TabInt TOut;
  int i;
  for(i=GetLastIdx(T);i>=GetFirstIdx(T);i--){
    Elmt(TOut, GetLastIdx(T)-i+1) = Elmt(T, i);
  }
  Neff(TOut) = NbElmt(T);
  return TOut;
}

boolean IsSimetris (TabInt T)
/* Menghasilkan true jika tabel simetrik */
/* Tabel disebut simetrik jika: */
/*      elemen pertama = elemen terakhir, */
/*      elemen kedua = elemen sebelum terakhir, dan seterusnya */
/* Tabel kosong adalah tabel simetris */
{
  int i=GetFirstIdx(T);
  boolean b = true;
  if(!IsEmpty(T)){
    while(i<=GetLastIdx(T)/2 && b){
      if(Elmt(T,i) != Elmt(T, GetLastIdx(T)-i+1)){
        b = false;
      }
      i++;
    }
  }
  
  return b;
}

/* ********** SORTING ********** */
void MaxSortDesc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menurun dengan Maximum Sort */
/* Proses : mengurutkan T sehingga elemennya menurun/mengecil */
/*          tanpa menggunakan tabel kerja */
{
  IdxType i,j,max, idmax;
  ElType temp;

  
  
  for(i=GetFirstIdx(*T);i<=GetLastIdx(*T);i++){
    max = Elmt(*T,i);
    idmax = i;
    for(j=i+1; j<=GetLastIdx(*T); j++){
      if(Elmt(*T, j)>max){
        idmax = j;
        max = Elmt(*T, j);
      }
    }

    temp = Elmt(*T,idmax);
    Elmt(*T,idmax) = Elmt(*T, i);
    Elmt(*T, i) = temp;
  }
}

void InsSortAsc (TabInt * T)
/* I.S. T boleh kosong */
/* F.S. T elemennya terurut menaik dengan Insertion Sort */
/* Proses : mengurutkan T sehingga elemennya menaik/membesar */
/*          tanpa menggunakan tabel kerja */
{
  int i,j=GetFirstIdx(*T);
  ElType temp;
  for(i=GetFirstIdx(*T)+1; i<=GetLastIdx(*T); i++){
    temp = Elmt(*T, i);
    j=i-1;
    while(j>GetFirstIdx(*T) && temp<Elmt(*T,j)){
      Elmt(*T, j+1) = Elmt(*T, j);
      j--;
    }

    if(Elmt(*T,j) <= temp){
      Elmt(*T, j+1) = temp;
    } else {
      Elmt(*T, j+1) = Elmt(*T, j);
      Elmt(*T, j) = temp;
    }
  }
}

/* ********** MENAMBAH ELEMEN ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElType X)
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
{
  Elmt(*T, GetLastIdx(*T)+1) = X;
  Neff(*T)++;
}

void AddEli (TabInt * T, ElType X, IdxType i)
/* Menambahkan X sebagai elemen ke-i tabel tanpa mengganggu kontiguitas 
   terhadap elemen yang sudah ada */
/* I.S. Tabel tidak kosong dan tidak penuh */
/*      i adalah indeks yang valid. */
/* F.S. X adalah elemen ke-i T yang baru */
/* Proses : Geser elemen ke-i+1 s.d. terakhir */
/*          Isi elemen ke-i dengan X */
{
  int j;
  for(j=GetLastIdx(*T); j>=i; j--){
    Elmt(*T, j+1) = Elmt(*T, j);
  }
  Elmt(*T, i) = X;
  Neff(*T)++;
}

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElType * X)
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
{
  *X = Elmt(*T, GetLastIdx(*T));
  Neff(*T)--;
}

void DelEli (TabInt * T, IdxType i, ElType * X)
/* Menghapus elemen ke-i tabel tanpa mengganggu kontiguitas */
/* I.S. Tabel tidak kosong, i adalah indeks efektif yang valid */
/* F.S. X adalah nilai elemen ke-i T sebelum penghapusan */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
/* Proses : Geser elemen ke-i+1 s.d. elemen terakhir */
/*          Kurangi elemen efektif tabel */
{
  int j;

  *X = Elmt(*T, i);
  for(j=i+1; j<=GetLastIdx(*T); j++){
    Elmt(*T, j-1) = Elmt(*T, j);
  }
  Neff(*T)--;
}

/* ********** TABEL DGN ELEMEN UNIK (SETIAP ELEMEN HANYA MUNCUL 1 KALI) ********** */
void AddElUnik (TabInt * T, ElType X)
/* Menambahkan X sebagai elemen terakhir tabel, pada tabel dengan elemen unik */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/*      dan semua elemennya bernilai unik, tidak terurut */
/* F.S. Jika tabel belum penuh, menambahkan X sbg elemen terakhir T, 
        jika belum ada elemen yang bernilai X. 
		Jika sudah ada elemen tabel yang bernilai X maka I.S. = F.S. 
		dan dituliskan pesan "nilai sudah ada" */
/* Proses : Cek keunikan dengan sequential search dengan sentinel */
/*          Kemudian tambahkan elemen jika belum ada */
{
  boolean found;
  int i=GetFirstIdx(*T);

  found = SearchSentinel(*T, X);

  if(found){
    printf("nilai sudah ada\n");
  } else {
    AddAsLastEl(T, X);
  }

}

/* ********** TABEL DGN ELEMEN TERURUT MEMBESAR ********** */
IdxType SearchUrut (TabInt T, ElType X)
/* Prekondisi: Tabel T boleh kosong. Jika tidak kosong, elemen terurut membesar. */
/* Mengirimkan indeks di mana harga X dengan indeks terkecil diketemukan */
/* Mengirimkan IdxUndef jika tidak ada elemen tabel bernilai X */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel kosong */
{
  int i=GetFirstIdx(T);
  IdxType idx;
  boolean found=false;

  while(i<=GetLastIdx(T) && !found){
    if(Elmt(T, i)==X){
      found = true;
    }
    i++;
  }

  if(!found){
    return IdxUndef;
  } else {
    return i-1;
  }
}

ElType MaxUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai maksimum pada tabel */
{
  return Elmt(T, GetLastIdx(T));
}

ElType MinUrut (TabInt T)
/* Prekondisi : Tabel tidak kosong, elemen terurut membesar */
/* Mengirimkan nilai minimum pada tabel*/
{
  return Elmt(T, GetFirstIdx(T));
}

void MaxMinUrut (TabInt T, ElType * Max, ElType * Min)
/* I.S. Tabel T tidak kosong, elemen terurut membesar */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
{
  *Max = Elmt(T, GetLastIdx(T));
  *Min = Elmt(T, GetFirstIdx(T));
}

void Add1Urut (TabInt * T, ElType X)
/* Menambahkan X tanpa mengganggu keterurutan nilai dalam tabel */
/* Nilai dalam tabel tidak harus unik. */
/* I.S. Tabel T boleh kosong, boleh penuh. */
/*      Jika tabel isi, elemennya terurut membesar. */
/* F.S. Jika tabel belum penuh, menambahkan X. */
/*      Jika tabel penuh, maka tabel tetap. */
/* Proses : Search tempat yang tepat sambil geser */
/*          Insert X pada tempat yang tepat tersebut tanpa mengganggu keterurutan */
{
  IdxType i = GetFirstIdx(*T);
  if(Neff(*T)+1<=IdxMax){
    while(i<=GetLastIdx(*T) && X>Elmt(*T,i)){
      i++;
    }
    AddEli(T, X, i);
  }
}

void Del1Urut (TabInt * T, ElType X)
/* Menghapus X yang pertama kali (pada indeks terkecil) yang ditemukan */
/* I.S. Tabel tidak kosong */
/* F.S. Jika ada elemen tabel bernilai X , */
/*      maka banyaknya elemen tabel berkurang satu. */
/*      Jika tidak ada yang bernilai X, tabel tetap. */
/*      Setelah penghapusan, elemen tabel tetap kontigu! */
/* Proses : Search indeks ke-i dengan elemen ke-i = X. */
/*          Delete jika ada. */
{
  int i=GetFirstIdx(*T);

  while(i<=GetLastIdx(*T) && Elmt(*T, i) != X){
    i++;
  }
  if(i<=GetLastIdx(*T)){
    DelEli(T, i, &X);
  }
}