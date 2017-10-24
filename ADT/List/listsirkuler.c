#include "listsirkuler.h"
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmpty (List L)
/* Mengirim true jika list kosong. Lihat definisi di atas. */
{
  return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmpty (List *L)
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
{
  First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  address P = (ElmtList *)malloc(sizeof(ElmtList));
  if(P != Nil){
    Info(P) = X;
    Next(P) = Nil;
  }
  return P;
}

void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
  free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X)
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
{
  address P = First(L);
  if(P != Nil){
    do {
      if(Info(P) == X){
        return P;
      }
      P = Next(P);
    } while(P != First(L));
  }
  return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  address P = Alokasi(X);
  if(P!=Nil){
    Next(P) = First(*L);
    address last = First(*L);
    while(Next(last) != First(*L)){
      last = Next(last);
    }
    First(*L) = P;
    Next(last) = First(*L);
  }
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{
  address P = Alokasi(X), temp = First(*L);
  if(P!=Nil){
    if(temp == Nil){
      Next(P) = First(*L);
      First(*L) = P;
    }
    else{
      while(Next(temp) != First(*L)){
        temp = Next(temp);
      }
      Next(temp) = P;
      Next(P) = First(*L);
    }
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype * X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  Info(First(*L)) = *X;
  address P = First(*L);
  First(*L) = Next(P);
  Dealokasi(P);
}

void DelVLast (List *L, infotype * X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  address temp = First(*L), prec = Nil;
  if(Next(temp) == Nil){
    *X = Info(temp);
    First(*L) = Nil;
  }
  else{
    while(Next(temp) != First(*L)){
      prec = temp;
      temp = Next(temp);
    }
    *X = Info(temp);
    Next(prec) = First(*L);
  }
  Dealokasi(temp);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  Next(P) = First(*L);
  address last = First(*L);
  while(Next(last) != First(*L)){
    last = Next(last);
  }
  First(*L) = P;
  Next(last) = First(*L);
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  address temp = First(*L);
  if(P!=Nil){
    if(temp == Nil){
      First(*L) = P;
      Next(P) = First(*L);
    }
    else{
      while(Next(temp) != First(*L)){
        temp = Next(temp);
      }
      Next(temp) = P;
      Next(P) = First(*L);
    }
  }
}

void InsertAfter (List *L, address P, address Prec)
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
{
  Next(P) = Next(Prec);
  Next(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
{
  *P = First(*L);
  First(*L) = Next(First(*L));
  if(First(*L) != Nil){
    address last = First(*L);
    while(Next(last) != First(*L)){
      last = Next(last);
    }
    Next(last) = First(*L);
  }
}

void DelLast (List *L, address *P)
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
{
  address last=First(*L), preclast=Nil;
  while(Next(last) != First(*L)){
    preclast = last;
    last = Next(last);
  }
  if(preclast == Nil){
    *P = last;
    First(*L) = Nil;
  }
  else{
    *P = last;
    Next(preclast) = First(*L);
  }
}
void DelAfter (List *L, address *Pdel, address Prec)
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
{
  *Pdel = Next(Prec);
  Next(Prec) = Next(*Pdel);
}

void DelP (List *L, infotype X)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
  address P = Search(*L, X), temp = First(*L), prec = Nil;
  if(P != Nil){
    while(temp != P){
      prec = temp;
      temp = Next(temp);
    }
    if(prec != Nil){
      Next(prec) = Next(temp);
    }
    else{
      First(*L) = Nil;
    }
    Dealokasi(P);
  }
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L)
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
{
  address P = First(L);
  printf("[");
  if(P != Nil){
    do {
      if(P == First(L)){
        printf("%d", Info(P));
      }
      else {
        printf(",%d", Info(P));
      }
      P = Next(P);
    } while(P != First(L));
  }
  printf("]");
}
