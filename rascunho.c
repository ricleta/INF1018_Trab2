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

void processa_ret(char var, int id, unsigned char * vetor)
{
  switch(var)
  {
    case 'v':
    {
      // Retorna variável
      switch (id)
      {
        // v0
        case 0:
        {
          vetor[0] = 0x89;
          vetor[1] = 0xd8;          
          vetor[2] = 0xc3;
          break;
        }
        case 1:
        {
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe0;
          vetor[3] = 0xc3;
          break;
        }
        case 2:
        {
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xe8;
          vetor[3] = 0xc3;
          break;
        }
        case 3:
        {
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf0;          
          vetor[3] = 0xc3;
          break;
        }
        case 4:
        {
          vetor[0] = 0x44;
          vetor[1] = 0x89;
          vetor[2] = 0xf8;         
          vetor[3] = 0xc3;
          break;
        }
      }
      break;
    }
    case 'p':
    {
      // Retorna parâmetro
      vetor[0] = 0x89;
      vetor[1] = 0xf8;
      vetor[2] = 0xc3;
      break;
    }
    case '$':
    {  
      // Retorna inteiro
      vetor[0] = 0xb8;
      
      unsigned char bytes[4];
      quebra_int(id, bytes);
      
      vetor[1] = bytes[0];
      vetor[2] = bytes[1];
      vetor[3] = bytes[2];
      vetor[4] = bytes[3];
      vetor[5] = 0xc3;
    
      break;
    }
  }
}

void processa_zret(char var1, int id1, char var2, int id2, unsigned char * vetor)
{
  unsigned char * ret  = malloc(6);
  processa_ret(var2, id2, ret);
  int byte_size;

  if(var2 == 'v')
  {
    if(id2 == 0)
    {   
      byte_size = 3;
    }
    else
    {
      byte_size = 4;
    }
  }
  else if(var2 == 'p')
  {
    byte_size = 3;
  }
  else
  {
    byte_size = 6;
  }
  
  int i = 0;
  
  switch(var1)
  {
    case 'v':
    {
      if(id1 != 0)
      {
        vetor[i] = 0x41;
        i++;
      }
      
      vetor[i] = 0x83;
      i++;
      
      switch (id1)
      {
        // v0
        case 0:
        {
          vetor[i] = 0xfb;    
          i++;
          break;
        }
        case 1:
        {
          vetor[i] = 0xfc; 
          i++;
          break;
        }
        case 2:
        {
          vetor[i] = 0xfd; 
          i++;
          break;
        }
        case 3:
        {
          vetor[i] = 0xfe; 
          i++;
          break;
        }
        case 4:
        {
          vetor[i] = 0xff; 
          i++;
          break;
        }
      }
      
      vetor[i] = 0x00;
      i++;
      
      vetor[i] = 0x75;
      i++;
      
      break;
    }
    case 'p':
    {
      vetor[i] = 0x83;
      i++;
      
      vetor[i] = 0xff;
      i++;
      
      vetor[i] = 0x00;
      i++;
      
      vetor[i] = 0x75;
      i++;
     
      break;
    }
    case '$':
    {
      if(id1 != 0)
      {
        //
      }
      
      break;
    }
  }
  
  if(var1 != '$')
  {
    vetor[i] = byte_size;
    i++;
  }
  
  for(int j=0; j<byte_size; j++)
  {
    vetor[i+j] = ret[j];
  }
  
  free(ret);
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

// Incompleto
unsigned char * aloca_variavel(int n, char var, int id)
{
  unsigned char * vetor = malloc(10);
  int i = 0;

  if(var == '$')
  {
    unsigned char * int_quebrado = malloc(4);
    quebra_int(id, int_quebrado);
    
    if(n != 0)
    {
      vetor[i] = 0x41;
      i++;
    }
    switch(n)
    {
      case 0:
      {
        vetor[i] = 0xbb;
        break;
      }
      case 1:
      {
        vetor[i] = 0xbc;
        break;
      }
      case 2:
      {
        vetor[i] = 0xbd;
        break;
      }
      case 3:
      {
        vetor[i] = 0xbe;
        break;
      }
      case 4:
      {
        vetor[i] = 0xbf;
        break;
      }
    }
    
    i++;
    
    for(int j=0; j < 4; j++)
    {
      vetor[i + j] = int_quebrado[j];
    }
    
    i += 4;
    
    unsigned char * aux = malloc(4);
    aux = aloca_variavel(n, 'v', n);
    
    for(int j=0; j<4; j++)
    {
      vetor[i+j] = aux[j];
    }
    
    i += 4;
    
    return vetor;
  }
  
  if(n != 0 && var == 'v')
  {
    vetor[i] = 0x44;
    i++;
  }
  
  vetor[i] = 0x89;
  i++;
  
  switch(var)
  {
    case 'v':
    {
      switch(id)
      {
        case 0:
        {
          vetor[i] = 0x5d;
          break;
        }
        case 1:
        {
          vetor[i] = 0x65;
          break;
        }
        case 2:
        {
          vetor[i] = 0x6d;
          break;
        }
        case 3:
        {
          vetor[i] = 0x75;
          break;
        }
        case 4:
        {
          vetor[i] = 0x7d;
          break;
        }
      }
      
      i++;
      break;
    }
    case 'p':
    {
      vetor[i] = 0x7d;
      i++;
    }
  }
  
  switch(n)
  {
    case 0:
    {
      vetor[i] = 0xfc;
      break;
    }
    case 1:
    {
      vetor[i] = 0xf8;
      break;
    }
    case 2:
    {
      vetor[i] = 0xf4;
      break;
    }
    case 3:
    {
      vetor[i] = 0xf0;
      break;
    }
    case 4:
    {
      vetor[i] = 0xec;
      break;
    }
  }
  
  i++;
  return vetor;
}

void processa_call(int called, int tam, int * funcs, unsigned char * vetor)
{
  unsigned char * buffer = malloc(19);

  guarda_pilha(buffer);
  concatena(vetor, 0, buffer, 19);
  
  vetor[20] = 0xe8;
  int t = 0 - tam + funcs[called];
  quebra_int(t, buffer);
  concatena(vetor, 20, buffer, 4);

  tira_pilha(buffer);
  concatena(vetor, 24, buffer, 19);
}

void quebra_int(int inteiro, unsigned char bytes[4])
{
  bytes[3] = (inteiro & 0xff000000) >> 24;
  bytes[2] = (inteiro & 0x00ff0000) >> 16;
  bytes[1] = (inteiro & 0x0000ff00) >> 8;
  bytes[0] = inteiro & 0x000000ff;
}


void concatena (unsigned char * arr1, int tam1, unsigned char * arr2, int tam2)
{
  for(int i=0; i < tam2; i++)
  {
    arr1[tam1 + i] = arr2[i];
  }
}

void guarda_pilha(unsigned char * vetor)
{
  unsigned char vetor_local[19] = {0x89, 0x5d, 0xfc, 0x44, 0x89, 0x65, 0xf8, 0x44, 0x89, 0x6d, 0xf4, 0x44, 0x89, 0x75, 0xf0, 0x44, 0x89, 0x7d, 0xec};
  
  for(int i=0; i < 19; i++)
  {
    vetor[i] = vetor_local[i];
  }
}

void tira_pilha(unsigned char * vetor)
{
  unsigned char vetor_local[19] = {0x8b, 0x5d, 0xfc, 0x44, 0x8b, 0x65, 0xf8, 0x44, 0x8b, 0x6d, 0xf4, 0x44, 0x8b, 0x75, 0xf0, 0x44, 0x8b, 0x7d, 0xec};
  
  for(int i=0; i < 19; i++)
  {
    vetor[i] = vetor_local[i];
  }
}

void gera_codigo (FILE *file, unsigned char code[], funcp *entry)
{ 
  char c;
  int line = 0;
  int * funcs = malloc(50 * sizeof(int));
  int tam_codigo = 0;
  int func_atual = 0;
  unsigned char * cdm = malloc(500);
  unsigned char * buffer = malloc(43);
  // FILE *file;

  tam_codigo += 8;

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
        funcs[func_atual] = tam_codigo;
        func_atual++;
    
        prologo(buffer);
        concatena(cdm, tam_codigo, buffer, 8);
        tam_codigo += 8;
        printf("function\n");
        break;
      }
      case 'e': 
      { /* end */
        char c0;
        if (fscanf(file, "nd%c", &c0) != 1)
        {
          perror("comando invalido");
        }
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
        
        processa_ret(var0, idx0, buffer);
        concatena(cdm, tam_codigo, buffer, 6);
        tam_codigo += 6;
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
        processa_zret(var0, idx0, var1, idx1, buffer);
        concatena(cdm, tam_codigo, buffer, 12);
        tam_codigo += 12;
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
          processa_call(f, tam_codigo, funcs, buffer);
          concatena(cdm, tam_codigo, buffer, 20);
          tam_codigo += 20;
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
      line ++;
      fscanf(file, " ");
    }  
  }
}
