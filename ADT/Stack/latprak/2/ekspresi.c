#include "stackt.h"
#include "mesintoken.h"
#include <stdio.h>
#include <math.h>

int Operasi(int op1, int op2, char op){
  if(op == '+'){
    return op1+op2;
  }
  else if(op == '-'){
    return op1-op2;
  }
  else if(op == '*'){
    return op1*op2;
  }
  else if(op == '/'){
    return op1/op2;
  }
  else if(op == '^'){
    return pow(op1, op2);
  }
}

int main(){
  Stack S;
  CreateEmpty(&S);
  int op1,op2;
  STARTTOKEN();
  if(EndToken){
    printf("Ekspresi kosong\n");
  }
  else{
    do {
      if(CToken.tkn=='b'){
        printf("%d\n", CToken.val);
        Push(&S, CToken.val);
      }
      else{
        Pop(&S, &op2);
        Pop(&S, &op1);
        Push(&S, Operasi(op1, op2, CToken.tkn));
        printf("%d %c %d\n", op1, CToken.tkn, op2);
        printf("%d\n", Operasi(op1, op2, CToken.tkn));
      }
      ADVTOKEN();
    } while(!EndToken);
    printf("Hasil=%d\n", Operasi(op1, op2, CToken.tkn));
  }

  return 0;
}
