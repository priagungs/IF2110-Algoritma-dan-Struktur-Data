#include "mesintoken.h"
#include <stdio.h>

int main(){
	Token token[10000];
	int i=0;
	STARTTOKEN();
	if(!EndToken){
		token[i] = CToken;
		i++;
		ADVTOKEN();
	}
	while(!EndToken){
		token[i] = CToken;
		i++;
		ADVTOKEN();
	}

	if(i==0){
		printf("Ekspresi kosong\n");
	}
	else {
		for(int j=0; j<i; j++){
			if(token[j].tkn != 'b'){
				printf("%c\n", token[j].tkn);
			}
			else{
				printf("%d\n", token[j].val);
			}
		}
	}
}