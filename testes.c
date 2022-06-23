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
        
    for(int i=0; i<12; i++){
      printf("Byte %d: %02x\n", i + 1, result[i]);
    }
  }
}

void testa_aloca(int * n, char * var, int * id, int num_testes){
   unsigned char * result;
  for(int j=0; j<num_testes; j++){
    result = aloca_variavel(n[j], var[j], id[j]);
    printf("Executando teste %d (v%d = %c%d):\n", j+1, n[j], var[j], id[j]);
        
    for(int i=0; i<10; i++){
      printf("Byte %d: %02x\n", i + 1, result[i]);
    }
  }
}
int main(){
 int n[15] = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
 char var[15] = {'v', 'v', 'v', 'v', 'v', 'p', 'p', 'p', 'p', 'p', '$', '$', '$', '$', '$'};
 int id[15] = {0, 2, 3, 4, 1, 0, 0, 0, 0, 0, 0, 1, -1, 300, -300};
  testa_aloca(n, var, id, 15);
  return 0;
}