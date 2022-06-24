#include <stdlib.h>

typedef struct vct{
  unsigned char * vetor;
  int tam;
} s_vct;

s_vct cria_vct(unsigned char * vetor){
  s_vct x;
  x.vetor = vetor;
  x.tam = 0;
  return x;
}
void quebra_int(int inteiro, unsigned char bytes[4])
{
  bytes[3] = (inteiro & 0xff000000) >> 24;
  bytes[2] = (inteiro & 0x00ff0000) >> 16;
  bytes[1] = (inteiro & 0x0000ff00) >> 8;
  bytes[0] = inteiro & 0x000000ff;
}

void concatena (s_vct arr1, unsigned char * arr2, int tam2)
{
  for(int i=0; i < tam2; i++)
  {
    arr1.vetor[arr1.tam + i] = arr2[i];
  }
  arr1.tam += tam2;
}

unsigned char pos_pilha(int id){
  return (unsigned char)((id+1) * -4);
}

void pilha_para_reg(int id, unsigned char * vetor){
  vetor[0] = 0xb8;
  vetor[1] = 0x5d;
  vetor[2] = pos_pilha(id);
}

void pilha_para_aux(int id, unsigned char * vetor){
  vetor[0] = 0x44;
  vetor[1] = 0xb8;
  vetor[2] = 0x65;
  vetor[3] = pos_pilha(id);
}

void reg_para_pilha(int id, unsigned char * vetor){
  vetor[0] = 0x89;
  vetor[1] = 0x5d;
  vetor[2] = pos_pilha(id);
}
void prologo( unsigned char * vetor)
{
  vetor[0] = 0x55;
  vetor[1] = 0x48;
  vetor[2] = 0x89;
  vetor[3] = 0xe5;
  vetor[4] = 0x48;
  vetor[5] = 0x83;
  vetor[6] = 0xec;
  vetor[7] = 0x20;
  }
void prep_ret (unsigned char * vetor){
  vetor[0] = 0x89;
  vetor[1] = 0xd8;
}
void prep_call (unsigned char * vetor){
  vetor[0] = 0x89;
  vetor[1] = 0xde;
}

void pega_ret(unsigned char * vetor){
  vetor[0] = 0x89;
  vetor[1] = 0xc3;
}

void ret(unsigned char * vetor){
  vetor[0] = 0xc9;
  vetor[1] = 0xc3;
}

void num_para_reg(int num, s_vct * arr){
  unsigned char * mini_buffer = malloc(4);
  
  arr->vetor[0] = 0xb8;
  arr->tam += 1;
  
  quebra_int(num, mini_buffer);
  concatena(*arr, mini_buffer, 4);
  free(mini_buffer);
}

void num_para_aux(int num, s_vct * arr){
  unsigned char * mini_buffer = malloc(4);

  arr->vetor[0] = 0x41;
  arr->vetor[1] = 0xbc;
  arr->tam += 2;
  
  quebra_int(num, mini_buffer);
  concatena(*arr, mini_buffer, 4);
  free(mini_buffer);
}

void operation(char op, unsigned char * vetor){
  switch(op){
    case '+':{
      vetor[0] = 0x44;
      vetor[1] = 0x01;
      vetor[2] = 0xe3;
      break;
    }
    case '-':{
      vetor[0] = 0x44;
      vetor[1] = 0x29;
      vetor[2] = 0xe3;
      break;
    }
    case '*':{
      vetor[0] = 0x41;
      vetor[1] = 0x0f;
      vetor[2] = 0xaf;
      vetor[3] = 0xdc;
      break;
    }
  }
}


