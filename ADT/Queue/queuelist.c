#include "queuelist.h"
#include <stdlib.h>

/* Prototype manajemen memori */
void Alokasi (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  *P = (ElmtQueue *)malloc(sizeof(ElmtQueue));
  if(*P != Nil){
    Next(*P) = Nil;
    Info(*P) = X;
  }
}

void Dealokasi (address  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  free(P);
}

boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
  return Head(Q) == Nil && Tail(Q) == Nil;
}

int NbElmt(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
{
  int count=0;
  if(!IsEmpty(Q)){
    count++;
    address P = Head(Q);
    while(P != Tail(Q)){
      count++;
      P = Next(P);
    }
  }
  return count;
}

void CreateEmpty(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
{
  Head(*Q) = Nil;
  Tail(*Q) = Nil;
}

void Add (Queue * Q, infotype X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
  address P;
  Alokasi(&P, X);
  if(P!=Nil){
    if(!IsEmpty(*Q)){
      Next(Tail(*Q)) = P;
      Tail(*Q) = P;
    }
    else{
      Head(*Q) = P;
      Tail(*Q) = P;
    }
  }
}

void Del(Queue * Q, infotype * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
  *X = InfoHead(*Q);
  if(Head(*Q) == Tail(*Q)){
    CreateEmpty(Q);
  }
  else{
    Head(*Q) = Next(Head(*Q));
  }
}
