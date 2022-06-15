#include <stdio.h>
#include <stdlib.h>
#include "rascunho.h"

void testa_quebra_int(int * testes, int num_testes){
  unsigned char bytes[4];
  for(int j=0; j < num_testes; j++){
    quebra_int(testes[j], bytes);
    printf("Executando teste %d (%d):\n", j+1, testes[j]);

    for(int i=0; i<4; i++){
      printf("Byte %d: %02x\n", i + 1, bytes[i]);
    }
  }
}

void testa_processa_ret(char * vars, int * ids, int num_testes){
  unsigned char * result;
  for(int j=0; j < num_testes; j++){
    result = processa_ret(vars[j], ids[j]);
    printf("Executando teste %d (%c%d):\n", j+1, vars[j], ids[j]);
    
    for(int i=0; i<6; i++){
      printf("Byte %d: %02x\n", i + 1, result[i]);
    }
    
  }
}


void testa_processa_zret(char * vars1, int *ids1, char *vars2, int *ids2, int num_testes){
  unsigned char * result;
  for(int j=0; j<num_testes; j++){
    result = processa_zret(vars1[j], ids1[j], vars2[j], ids2[j]);
    printf("Executando teste %d (%c%d %c%d):\n", j+1, vars1[j], ids1[j], vars2[j], ids2[j]);
        
    for(int i=0; i<11; i++){
      printf("Byte %d: %02x\n", i + 1, result[i]);
    }
  }
}
int main(){

  return 0;
}