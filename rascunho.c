#include <stdio.h>
#include <stdlib.h>
#include "gera_codigo.h"
#include "rascunho.h"

/*
int main(int argc, char *argv[])
{
  FILE *fp;
  unsigned char code[300];
  funcp funcLBS;
  // int res = 0;
  
  fp = fopen("lbs1.txt", "r");

  gera_codigo(fp, code, &funcLBS);
  // if (funcLBS == NULL) 
  // {
  //   printf("Erro na geracao\n");
  // }
  
  // res = (*funcLBS)(12);

  return 0;
}
*/

unsigned char * processa_ret(char var, int id){
  unsigned char * vetor = malloc(6);
  switch(var){
    case 'v':{
      // Retorna variável
      
      switch (id){
        // v0
        case 0:{
          vetor[0] = 0x89;
          vetor[1] = 0xd8;          
          vetor[2] = 0xc3;
          break;
        }
        case 1:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe0;
          vetor[3] = 0xc3;
          break;
        }
        case 2:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe8;
          vetor[3] = 0xc3;
          break;
        }
        case 3:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf0;          
          vetor[3] = 0xc3;
          break;
        }
        case 4:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf8;         
          vetor[3] = 0xc3;
          break;
        }
      }
      break;
    }
    case 'p':{
      // Retorna parâmetro
      vetor[0] = 0x89;
      vetor[1] = 0xf8;
      vetor[2] = 0xc3;
      break;
    }
    case '$':{
      
      // Retorna inteiro
      vetor[0] = 0xb8;
      
      unsigned char bytes[4];
      quebra_int(id, bytes);
      
      vetor[1] = bytes[3];
      vetor[2] = bytes[2];
      vetor[3] = bytes[1];
      vetor[4] = bytes[0];
      vetor[5] = 0xc3;
    
      break;
    }

  }
  return vetor;
}
unsigned char * processa_zret(char var1, int id1, char var2, int id2){
  unsigned char * vetor = malloc(9);
  unsigned char * ret;
  switch(var1){
    case 'v':{
        ret = processa_ret(var2, id2);
        switch (id1){
        // v0
        case 0:{
          vetor[0] = 0x83;
          vetor[1] = 0xfb;          
          vetor[2] = 0x00;
          vetor[3] = 0x75;
          vetor[4] = 0x03;
          vetor[5] = ret[0];
          vetor[6] = ret[1];
          vetor[7] = ret[2];
          break;
        }
        case 1:{
          vetor[0] = 0x41;
          vetor[1] = 0x83;
          vetor[2] = 0xfc;
          vetor[3] = 0x00;     
          vetor[4] = 0x75;         
          vetor[5] = 0x04;
          vetor[6] = ret[0];
          vetor[7] = ret[1];
          vetor[8] = ret[2];
          vetor[9] = ret[3];
          break;
        }
        case 2:{
          vetor[0] = 0x41;
          vetor[1] = 0x83;
          vetor[2] = 0xfd;
          vetor[3] = 0x00;
          vetor[4] = 0x75;
          vetor[5] = 0x04;
          vetor[6] = ret[0];
          vetor[7] = ret[1];
          vetor[8] = ret[2];
          vetor[9] = ret[3];
          break;
        }
        case 3:{
          vetor[0] = 0x41;
          vetor[1] = 0x83;
          vetor[2] = 0xfe;          
          vetor[3] = 0x00;
          vetor[4] = 0x75;
          vetor[5] = 0x04;
          vetor[6] = ret[0];
          vetor[7] = ret[1];
          vetor[8] = ret[2];
          vetor[9] = ret[3];
          break;
        }
        case 4:{
          vetor[0] = 0x41;
          vetor[1] = 0x83;
          vetor[2] = 0xff;         
          vetor[3] = 0x00;
          vetor[4] = 0x75;  
          vetor[5] = 0x04;
          vetor[6] = ret[0];
          vetor[7] = ret[1];
          vetor[8] = ret[2];
          vetor[9] = ret[3];
          break;
        }
      }
      break;
    }
    case 'p':{
      ret = processa_ret(var2, id2);
      vetor[0] = 0x83;
      vetor[1] = 0xff;
      vetor[2] = 0x00;
      vetor[3] = 0x75;
      vetor[4] = 0x03;
      vetor[5] = ret[0];
      vetor[6] = ret[1];
      vetor[7] = ret[2];
      break;
    }
    case '$':{
      if(id1 == 0){
        ret = processa_ret(var2, id2);
        vetor[0] = ret[0];
        vetor[1] = ret[1];
        vetor[2] = ret[2];
        vetor[3] = ret[3];
        vetor[4] = ret[4];
        vetor[5] = ret[5];
      break;
    }
  }
}
void quebra_int(int inteiro, unsigned char bytes[4]){
  bytes[0] = (inteiro & 0xff000000) >> 24;
  bytes[1] = (inteiro & 0x00ff0000) >> 16;
  bytes[2] = (inteiro & 0x0000ff00) >> 8;
  bytes[3] = inteiro & 0x000000ff;
}
void gera_codigo (FILE *file, unsigned char code[], funcp *entry)
{
  int line = 1;
  int  c;
  int tam_codigo = 0;
  int * inicio = malloc(50 * sizeof(int));
  int * fim = malloc(50 * sizeof(int));
  // FILE *file;

  if (file == NULL) 
  {
    perror ("nao conseguiu abrir arquivo!");
    exit(1);
  }

  while ((c = fgetc(file)) != EOF) 
  {
    switch (c) 
    {
      case 'f': 
      { /* function */
        char c0;
        if (fscanf(file, "unction%c", &c0) != 1)
        {
          perror("comando invalido1");
        }
        *inicio = tam_codigo;
        break;
      }
      case 'e': 
      { /* end */
        char c0;
        if (fscanf(file, "nd%c", &c0) != 1)
        {
          perror("comando invalido");
        }
        *fim = tam_codigo;
        printf("end\n");
        break;
      }
      case 'r': 
      {  /* retorno incondicional */
        int idx0;
        char var0;
        
        if (fscanf(file, "et %c%d", &var0, &idx0) != 2)
        {
          perror("comando invalido");
        }
        
        printf("ret %c%d\n", var0, idx0);
        break;
      }
      case 'z': 
      {  /* retorno condicional */
        int idx0, idx1;
        char var0, var1;
        
        if (fscanf(file, "ret %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4)
        {
          perror("comando invalido");
        }
        
        printf("zret %c%d %c%d\n", var0, idx0, var1, idx1);
        break;
      }
      case 'v': 
      {  /* atribuicao */
        int idx0;
        char var0 = c, c0;
        
        if (fscanf(file, "%d = %c",&idx0, &c0) != 2)
        {
          perror("comando invalido");
        }

        if (c0 == 'c') 
        { /* call */
          int f, idx1;
          char var1;
          
          if (fscanf(file, "all %d %c%d\n", &f, &var1, &idx1) != 3)
          {
            perror("comando invalido");
          }
          
          printf("%c%d = call %d %c%d\n",var0, idx0, f, var1, idx1);
        }
        else 
        { /* operaÃ§Ã£o aritmÃ©tica */
          int idx1, idx2;
          char var1 = c0, var2, op;
          
          if (fscanf(file, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
          {
            perror("comando invalido");
          }
          
          printf("%c%d = %c%d %c %c%d\n", var0, idx0, var1, idx1, op, var2, idx2);
        }

        break;
      }
      default: perror("comando desconhecido");
    }
    line ++;
    fscanf(file, " ");
  }  
}