#include <stdlib.h>
#include "auxiliares.h"

void processa_function(int ** funcs, int * func_atual, s_vct * cdm){
  unsigned char * buffer = malloc(8);
  
  *funcs[*func_atual] = cdm->tam;
  *func_atual += 1;

  prologo(buffer);
  concatena(*cdm, buffer, 8);
}

void processa_end(s_vct * cdm){
  unsigned char local[2] = {0xc9, 0xc3}; 
  concatena(*cdm, local, 2);
}

void processa_ret(char var, int id, s_vct * cdm){
  unsigned char * buffer = malloc(100);
  if(var == '$'){
    cdm->vetor[cdm->tam] = 0xb8;
    cdm->tam += 1;

    quebra_int(id, buffer);
    concatena(*cdm, buffer, 4);
  }
  else{
    if(var == 'p'){
      id = 5;
    }
    pilha_para_reg(id, buffer);
    concatena(*cdm, buffer, 3);
  }
    prep_ret(buffer);
    concatena(*cdm, buffer, 2);

    ret(buffer);
    concatena(*cdm, buffer, 2);
  
    free(buffer);
}

void processa_zret(char var1, int id1, s_vct * cdm, char var2, int id2){
  unsigned char * buffer = malloc(100);
  if(var1 == '$'){
    if(id1 == 0){
      if(var2 == '$'){
        cdm->vetor[cdm->tam] = 0xbb;
        cdm->tam += 1;

        quebra_int(id2, buffer);
        concatena(*cdm, buffer, 4);

      }
      else{
        pilha_para_reg(id2, buffer);
        concatena(*cdm, buffer, 3);
      }
    }
    else{
      free(buffer);
      return;
    }
  }
  else{
    if(var1 == 'p'){
      id1 = 5;
    }
    pilha_para_reg(id1, buffer);

    unsigned char local[5] = {0x83, 0xfb, 0x00, 0x75, 0x04};
    concatena(*cdm, local, 5);

    if(var2 == '$'){
      num_para_reg(id2, cdm);
    }
    else{
      if(var2 == 'p'){
        id2 = 5;
      }

      pilha_para_reg(id2, buffer);
      concatena(*cdm, buffer, 3);
      
      prep_ret(buffer);
      concatena(*cdm, buffer, 2);
    }
  } 
    ret(buffer);
    concatena(*cdm, buffer, 2);
  free(buffer);
}

void processa_call(char varp, int idp, int id, int called, int * funcs, s_vct * cdm){
  int t;
  unsigned char * buffer = malloc(50);

  if(varp == '$'){
    num_para_reg(idp, cdm);
  }
  else{
    if(varp == 'p'){
      idp = 5;
    }
    pilha_para_reg(idp, buffer);
    concatena(*cdm, buffer, 3);
  }

  prep_call(buffer);
  concatena(*cdm, buffer, 2);
  
  cdm->vetor[cdm->tam] = 0xe8;
  cdm->tam++;

  t = funcs[called] - cdm->tam;  
  quebra_int(t, buffer);
  concatena(*cdm, buffer, 4);

  pega_ret(buffer);
  concatena(*cdm, buffer, 2);
  
  reg_para_pilha(id, buffer);
  concatena(*cdm, buffer, 3);
  
  free(buffer);
}

void processa_op(int id1, char var2, int id2, char op, char var3, int id3, s_vct * cdm){
  unsigned char * buffer = malloc(50);

  if(var2 == '$'){
    num_para_reg(id2, cdm);
  }
  else{
  pilha_para_reg(id2, buffer);
  concatena(*cdm, buffer, 3);
  }

  if(var3 == '$'){
    num_para_aux(id3, cdm);
  }
  else{
  pilha_para_aux(id3, buffer);
  concatena(*cdm, buffer, 4);
  }

  operation(op, buffer);
  concatena(*cdm, buffer, 4);

  reg_para_pilha(id1, buffer);
  concatena(*cdm, buffer, 3);

  free(buffer);
}

