#include <stdlib.h>
#include "auxiliares.h"

void processa_function(int ** funcs, int * func_atual, int * tam_codigo, unsigned char * cdm){
  unsigned char * buffer = malloc(8);
  
  *funcs[*func_atual] = *tam_codigo;
  *func_atual += 1;

  prologo(buffer);
  concatena(cdm, tam_codigo, buffer, 8);
}

void processa_end(unsigned char * cdm, int * tam_codigo){
  unsigned char local[2] = {0xc9, 0xc3}; 

  concatena(cdm, tam_codigo, local, 2);
}

void processa_ret(char var, int id, unsigned char * cdm, int * tam_codigo){
  unsigned char * buffer = malloc(100);
  if(var == '$'){
    cdm[*tam_codigo] = 0xb8;
    *tam_codigo += 1;

    quebra_int(id, buffer);
    concatena(cdm, tam_codigo, buffer, 4);
  }
  else{
    if(var == 'p'){
      id = 5;
    }
    pilha_para_reg(id, buffer);
    concatena(cdm, tam_codigo, buffer, 3);
  }
    prep_ret(buffer);
    concatena(cdm, tam_codigo, buffer, 2);

    ret(buffer);
    concatena(cdm, tam_codigo, buffer, 2);
  
    free(buffer);
}

void processa_zret(char var1, int id1, unsigned char * cdm, int * tam_codigo, char var2, int id2){
  unsigned char * buffer = malloc(100);
  if(var1 == '$'){
    if(id1 == 0){
      if(var2 == '$'){
        cdm[*tam_codigo] = 0xbb;
        *tam_codigo += 1;

        quebra_int(id2, buffer);
        concatena(cdm, tam_codigo, buffer, 4);

      }
      else{
        pilha_para_reg(id2, buffer);
        concatena(cdm, tam_codigo, buffer, 3);
      }
    }
    else{
      return;
    }
  }
  else{
    if(var1 == 'p'){
      id1 = 5;
    }
    pilha_para_reg(id1, buffer);

    unsigned char local[5] = {0x83, 0xfb, 0x00, 0x75, 0x04};
    concatena(cdm, tam_codigo, buffer, 5);

    if(var2 == '$'){
      
    }
  }
}