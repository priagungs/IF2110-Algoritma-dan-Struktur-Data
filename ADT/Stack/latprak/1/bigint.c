#include "stackt.h"
#include "boolean.h"
#include <stdio.h>

// Latihan Praktikum
// Nama : Priagung Satyagama
// NIM : 13516089
// Topik : ADT Stack

int CharToint(char c){
  return c - '0';
}

int CountStrLength(char s[]){
  int i=0;
  do{
    i++;
  } while(s[i] != '#');
  return i;
}

void SumMod10(int a, int b, int *sum, int *rem, int c){
  *sum = (a+b+c)%10;
  *rem = (a+b+c)/10;
}

int main(){
  char input1[110], input2[110];
  Stack s1,s2,SPlus;
  CreateEmpty(&s1);
  CreateEmpty(&s2);
  CreateEmpty(&SPlus);

  scanf("%s", input1);
  scanf("%s", input2);

  if(CountStrLength(input1) > CountStrLength(input2)){
    int a = CountStrLength(input2);
    do {
      Push(&s2, 0);
      a++;
    } while(a<CountStrLength(input1));
  }
  else   if(CountStrLength(input1) < CountStrLength(input2)){
    int a = CountStrLength(input1);
    do{
      Push(&s1, 0);
      a++;
    }while(a<CountStrLength(input2));
  }

  int i=0;
  while(input1[i] != '#'){
    Push(&s1, CharToint(input1[i]));
    i++;
  }
  i=0;
  while(input2[i] != '#'){
    Push(&s2, CharToint(input2[i]));
    i++;
  }

  int sum, rem=0, temp;
  int els1, els2;
  while(!IsEmpty(s1)){
    Pop(&s1, &els1);
    Pop(&s2, &els2);
    SumMod10(els1,els2,&sum,&temp,rem);
    Push(&SPlus, sum);
    rem=temp;
  }
  if(rem!=0){
    Push(&SPlus, rem);
  }

  while(!IsEmpty(SPlus)){
    int elSPlus;
    Pop(&SPlus, &elSPlus);
    printf("%d", elSPlus);
  }
  printf("\n");
}
