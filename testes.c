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

int main(){
  char vars[15] = {'v', 'v', 'v', 'v', 'v', 'p', '$', '$', '$', '$', '$', '$', '$', '$', '$'};
  
  int ids[15] = {0, 1, 2, 3, 4, 0, 0, 1, -1, 300, -300, 70000, -70000, 19000000, -19000000};
  testa_processa_ret(vars, ids, 15);
  return 0;
}