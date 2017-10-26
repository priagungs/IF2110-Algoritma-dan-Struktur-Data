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
    InsertFirst(L,P);
  }
}
void InsVLast (List *L, infotype X)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
{

  address P = Alokasi(X);
  if(P!=Nil){
    InsertLast(L,P);
  }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype * X)
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
{
  *X = Info(First(*L));
  address P;
  DelFirst(L, &P);
  Dealokasi(P);
}

void DelVLast (List *L, infotype * X)
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
{
  address last = First(*L), prec = Nil;
  while(Next(last) != First(*L)){
    prec = last;
    last = Next(last);
  }
  if(prec == Nil){
    *X = Info(last);
    CreateEmpty(L);
  }
  else {
    *X = Info(last);
    Next(prec) = First(*L);
  }
  Dealokasi(last);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
{
  InsertLast(L,P);
  First(*L) = P;
}

void InsertLast (List *L, address P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
{
  if(IsEmpty(*L)){
    First(*L) = P;
    Next(P) = First(*L);
  }
  else{
    address temp = First(*L);
    while(Next(temp) != First(*L)){
      temp = Next(temp);
    }
    InsertAfter(L,P,temp);
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
  if(Next(First(*L)) == First(*L)){
    *P = First(*L);
    First(*L) = Nil;
  }
  else {
    *P = First(*L);
    First(*L) = Next(First(*L));
    address preclast = First(*L);
    while(Next(preclast) != *P){
      preclast = Next(preclast);
    }
    Next(preclast) = First(*L);
    Next(*P) = Nil;
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
  address P = Search(*L, X), temp;
  if(P != Nil){
    if(P == First(*L) && Next(P) == P){ //if L just contain 1 element
      CreateEmpty(L);
    }
    else {
      address precP = First(*L);
      while(Next(precP) != P){
        precP = Next(precP);
      }
      if(Next(precP) == First(*L)){ //if P is first element of L
        First(*L) = Next(P);
      }
      Next(precP) = Next(P);
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
