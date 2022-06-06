#include <stdio.h>
#include <stdlib.h>
#include "gera_codigo.h"

int main(int argc, char *argv[])
{
  FILE *fp;
  unsigned char code[300];
  funcp funcLBS;
  // int res = 0;
  
  /* Abre o arquivo para leitura */
  fp = fopen("lbs1.txt", "r");

  /* Gera o codigo */
  gera_codigo(fp, code, &funcLBS);
  // if (funcLBS == NULL) 
  // {
  //   printf("Erro na geracao\n");
  // }
  
  /* Chama a função gerada */
  // res = (*funcLBS)(12);

  return 0;
}

unsigned char * processa_ret(char var, int id){
  unsigned char * vetor = malloc(3);
  switch(var){
    case 'v':{
      // Retorna variável
      switch (id){
        // v0
        case 0:{
          vetor[0] = 0x89;
          vetor[1] = 0xd8;
          break;
        }
        case 1:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe0;
          break;
        }
        case 2:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe8;
          break;
        }
        case 3:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf0;
          break;
        }
        case 4:{
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf8;
          break;
        }
      }
      break;
    }
    case 'p':{
      // Retorna parâmetro
      vetor[0] = 0x89;
      vetor[1] = 0xf8;
      break;
    }
    case '$':{
      // Retorna inteiro
      break;
    }
  }
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