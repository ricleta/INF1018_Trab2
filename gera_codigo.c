/*
  Rafael Paladini Meirelles 2111538 3WA 
  Ricardo Bastos Leta Vieira 2110526 3WA 
*/

#include <stdio.h>
#include <stdlib.h>
#include "gera_codigo.h"

// tipo ponteiro para função que recebe um inteiro e retorna um inteiro
typedef int (*funcp) (int x);

// struct formada por um array de unsigned char e uma int
// o array guarda o codigo de maquina em hexadecimal
// a int armazena o tamanho do array
// trata-se de uma estrutura auxiliar para manter o vetor e seu tamanho juntos e facilitar sua manipulacao
typedef struct vct
{
  unsigned char * vetor;
  int tam;
} s_vct;

// recebe um array e retorna uma struct s_vct com tamanho 0 e vetor igual ao recebido
// serve para iniciar a struct
s_vct cria_vct(unsigned char * vetor)
{
  s_vct x;
  x.vetor = vetor;
  x.tam = 0;
  return x;
}

// recebe um numero inteiro e um vetor de unsigned char de tamanho 4
// usa bitwise operator para separar os 4 bytes que forma a int
// e armazena cada byte em little endian no vetor de unsigend char
void quebra_int(int inteiro, unsigned char bytes[4])
{
  bytes[3] = (inteiro & 0xff000000) >> 24;
  bytes[2] = (inteiro & 0x00ff0000) >> 16;
  bytes[1] = (inteiro & 0x0000ff00) >> 8;
  bytes[0] = inteiro & 0x000000ff;
}

// recebe uma struct vetor, um array de unsigned char e um inteiro representando o tamanho do array de unsigned char
// adiciona os valores do segundo vetor ao final do vetor armazenado na struct
void concatena (s_vct *arr1, unsigned char * arr2, int tam2)
{
  // loop que itera pelo arr2
  for(int i=0; i < tam2; i++)
  {
    // para cada elemento de arr2, coloca o elemento na posicao igual ao final do vetor arr1 + a posicao do elemento no arr2 
    arr1->vetor[arr1->tam + i] = arr2[i];
  }

  // adiciona o tamanho do arr2 ao tamanho do arr1
  arr1->tam += tam2;
}

// funcao que encontra a posicao de um valor na pilha
// sendo uma variavel representada por vI, onde 0 <= I <= 4
// o id é o valor de I e a posicao é I + 1 * -4
// 4 pois os valores sao ints e I+1 pois a posicao nao pode ser 0
unsigned char pos_pilha(int id)
{
  return (unsigned char)((id+1) * -4); 
}

// escreve o codigo de maquina que equivale ao mov de um valor da pilha para um registrador (%ebx) em um buffer
void pilha_para_reg(int id, unsigned char * vetor)
{
  vetor[0] = 0x8b;
  vetor[1] = 0x5d;
  vetor[2] = pos_pilha(id);
}

// escreve o codigo de maquina que equivale ao mov de um valor da pilha para um registrador (%r12d) em um buffer
void pilha_para_aux(int id, unsigned char * vetor)
{
  vetor[0] = 0x44;
  vetor[1] = 0x8b;
  vetor[2] = 0x65;
  vetor[3] = pos_pilha(id);
}

// escreve o codigo de maquina que equivale ao mov de um registrador (%ebx) para um valor da pilha em um buffer
void reg_para_pilha(int id, unsigned char * vetor)
{
  vetor[0] = 0x89;
  vetor[1] = 0x5d;
  vetor[2] = pos_pilha(id);
}

/*
armazena o codigo de maquina equivalente ao seguinte codigo assembly
  push   %rbp
  mov    %rsp,%rbp
  sub    $0x20,%rsp
que aloca 32 (0x20) bytes na pilha
*/
void prologo(unsigned char * vetor)
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

// escreve o codigo de maquina que equivale ao mov de um registrador (%ebx) para o registrador de retorno (%eax) em um buffer
void prep_ret (unsigned char * vetor)
{
  // mov    %ebx,%eax
  vetor[0] = 0x89;
  vetor[1] = 0xd8;
}

// escreve o codigo de maquina que equivale ao mov de um valor da pilha para o registrador de primeiro argumento (%edi) em um buffer
void pilha_para_parametro(int id, unsigned char * vetor)
{
  vetor[0] = 0x8b;
  vetor[1] = 0x7d;
  vetor[2] = pos_pilha(id);
}

// escreve o codigo de maquina que equivale ao mov do valor no registrador de primeiro argumento (%edi) para uma posicao da pilha (-0x18(%rbp)) em um buffer
void salva_parametro (unsigned char * vetor)
{
  vetor[0] = 0x89;
  vetor[1] = 0x7d;
  vetor[2] = 0xe8;
}


// escreve o codigo de maquina que equivale ao mov do valor do registrador de retorno (%eax) para um registrador (%ebx) em um buffer
void pega_ret(unsigned char * vetor)
{
  vetor[0] = 0x89;
  vetor[1] = 0xc3;
}

/*
armazena o codigo de maquina equivalente ao seguinte codigo assembly
  leaveq 
  retq
*/
void ret(unsigned char * vetor)
{
  vetor[0] = 0xc9;
  vetor[1] = 0xc3;
}

// armazena um numero no formato $n, onde n é um numero inteiro qualquer, em um registrador (%ebx)
void num_para_reg(int num, s_vct * arr)
{
  // buffer de 4 bytes para armazenar os bytes separados do inteiro
  unsigned char * mini_buffer = malloc(4);

  // escreve em um byte o codigo de maquina para o mov de uma constante para um registrador, e aumenta o tamanho do vetor em 1
  arr->vetor[arr->tam] = 0xbb;
  arr->tam += 1;
  
  quebra_int(num, mini_buffer);
  concatena(arr, mini_buffer, 4); // coloca a int nos 4 bytes apos a indicacao de mov
  
  free(mini_buffer);
}

// armazena um numero no formato $n, onde n é um numero inteiro qualquer, em um registrador (%r12d)
void num_para_aux(int num, s_vct * arr)
{
  // buffer de 4 bytes para armazenar os bytes separados do inteiro
  unsigned char * mini_buffer = malloc(4);

  // escreve em 2 bytes o codigo de maquina para o mov de uma constante para um registrador, e aumenta o tamanho do vetor em 2
  arr->vetor[arr->tam] = 0x41;
  arr->vetor[arr->tam + 1] = 0xbc;
  arr->tam += 2;
  
  quebra_int(num, mini_buffer);
  concatena(arr, mini_buffer, 4); // coloca a int nos 4 bytes apos a indicacao de mov
  
  free(mini_buffer);
}

// armazena um numero no formato $n, onde n é um numero inteiro qualquer, em um registrador de primeiro argumento (%edi)
void num_para_parametro(int num, s_vct *arr)
{
  unsigned char * mini_buffer = malloc(4);

  arr->vetor[arr->tam] = 0xbf;
  arr->tam += 1;

  quebra_int(num, mini_buffer);
  concatena(arr, mini_buffer, 4);
  
  free(mini_buffer);
}

// recebe um char que indica qual operacao aritimetica sera feita
// e um vetor do codigo de maquina
// coloca o codigo de maquina adequado a cada operador no vetor
void operation(char op, unsigned char * vetor)
{
  switch(op)
  {
    case '+':
    {
      vetor[0] = 0x44;
      vetor[1] = 0x01;
      vetor[2] = 0xe3;
      break;
    }
    case '-':
    {
      vetor[0] = 0x44;
      vetor[1] = 0x29;
      vetor[2] = 0xe3;
      break;
    }
    case '*':
    {
      vetor[0] = 0x41;
      vetor[1] = 0x0f;
      vetor[2] = 0xaf;
      vetor[3] = 0xdc;
      break;
    }
  }
}

// recebe um ponteiro para um array de int que armazena as posicoes de funcoes na memoria
// recebe um ponteiro para a int que armazena o numero de funcao atual 
// recebe um ponteiro para a s_vct que armazena o vetor com o codigo de maquina e o seu tamanho
void processa_function(int * funcs, int * func_atual, s_vct * cdm)
{
  unsigned char * buffer = malloc(8);   

  // a posicao da funcao atual == ao tamanho do vetor com o codigo de maquina agora
  funcs[*func_atual] = cdm->tam;
  *func_atual += 1; // atualiza o valor de qual é a funcao atual

  // escreve prologo no buffer
  prologo(buffer);
  concatena(cdm, buffer, 8);

  // escreve parametro no buffer
  salva_parametro(buffer);
  concatena(cdm, buffer, 3);
}

/*
escreve o codigo de maquina equivalente a
  leaveq
  retq
no buffer (intrucao de end em lbs)
*/
void processa_end(s_vct * cdm)
{
  unsigned char local[2] = {0xc9, 0xc3}; 
  concatena(cdm, local, 2);
}

// escreve o codigo de maquina para retorna um valor
void processa_ret(char var, int id, s_vct * cdm)
{
  unsigned char * buffer = malloc(100);

  // se o calor for uma constante, move ele para um registrador
  if(var == '$')
  {
    num_para_reg(id, cdm);
  }
  else
  {
    // se for um parametro muda o id para 5
    if(var == 'p')
    {
      id = 5;
    }

    // se for parametro ou variavel escreve o buffer o codigo correspondente ao mov adequado
    pilha_para_reg(id, buffer);
    concatena(cdm, buffer, 3);
  }

  // move de um registrador para o registrador de retorno e escreve no buffer
  prep_ret(buffer);
  concatena(cdm, buffer, 2);
  
  free(buffer);
}

// escreve o codigo de maquina para um retorno condicional
void processa_zret(char var1, int id1, s_vct * cdm, char var2, int id2)
{
  unsigned char * buffer = malloc(100);

  // checa se o primeiro valor é uma constante
  if(var1 == '$')
  {
    // checa se seu id é 0
    if(id1 == 0)
    {
      // checa se o segundo valor é uma constante
      if(var2 == '$')
      {
        // se for, escreve o segundo valor em um registrador
        num_para_reg(id2, cdm);
      }
      else
      {
        // se nao, move o valor da pilha para um registrador e escreve o mov no vetor
        pilha_para_reg(id2, buffer);
        concatena(cdm, buffer, 3);
      }
    }
    else
    {
      // se id != 0, erro
      free(buffer);
      return;
    }
  }
  else
  {
    // se for parametro, muda id para 5
    if(var1 == 'p')
    {
      id1 = 5;
    }
    
    pilha_para_reg(id1, buffer);
    concatena(cdm, buffer, 3);

    // escreve codigo de maquina que compara %ebx com outro registrador
    unsigned char local[5] = {0x83, 0xfb, 0x00, 0x75, 0x09};
    concatena(cdm, local, 5);

    // se for uma constante, a coloca em um regitrador
    if(var2 == '$')
    {
      num_para_reg(id2, cdm);
    }
    else
    { 
      if(var2 == 'p')
      {
        id2 = 5;
      }

      pilha_para_reg(id2, buffer);
      concatena(cdm, buffer, 3);
    }

    // bota resultado da comparacao no registrador de retorno
    prep_ret(buffer);
    concatena(cdm, buffer, 2);
  } 

  // retorna o valor adequado
  ret(buffer);
  concatena(cdm, buffer, 2);
  
  free(buffer);
}

void processa_call(char varp, int idp, int id, int called, int * funcs, s_vct * cdm)
{
  int t;
  unsigned char * buffer = malloc(50);

  if(varp == '$')
  {
    num_para_parametro(idp, cdm);
  }
  else
  {
    if(varp == 'p')
    {
      idp = 5;
    }
    
    pilha_para_parametro(idp, buffer);
    concatena(cdm, buffer, 3);
  }

  // coloca byte que indica call no vetor do codigo de maquina 
  cdm->vetor[cdm->tam] = 0xe8;
  cdm->tam += 1;

  // operacao que encontra a posicao da funcao a ser chamada e armazena na variavel t
  t = &(cdm->vetor[funcs[called]]) - (&(cdm->vetor[cdm->tam]) + 4);

  quebra_int(t, buffer);
  concatena(cdm, buffer, 4);

  pega_ret(buffer);
  concatena(cdm, buffer, 2);
  
  reg_para_pilha(id, buffer);
  concatena(cdm, buffer, 3);
  
  free(buffer);
}

void processa_op(int id1, char var2, int id2, char op, char var3, int id3, s_vct * cdm)
{
  unsigned char * buffer = malloc(50);

  if(var2 == '$')
  {
    num_para_reg(id2, cdm);
  }
  else
  {
    if(var2 == 'p')
    {
      id2 = 5;
    }
    
    pilha_para_reg(id2, buffer);
    concatena(cdm, buffer, 3);
  }

  if(var3 == '$')
  {
    num_para_aux(id3, cdm);
  }
  else
  {
    if(var3 ==  'p')
    {
      id3 = 5;
    }
    
    pilha_para_aux(id3, buffer);
    concatena(cdm, buffer, 4);
  }

  operation(op, buffer);
  
  if(op == '*')
  {
    concatena(cdm, buffer, 4);
  }
  else
  {
    concatena(cdm, buffer, 3);
  }
  
  reg_para_pilha(id1, buffer);
  concatena(cdm, buffer, 3);

  free(buffer);
}

static void error(const char *msg, int line) 
{
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

void gera_codigo (FILE *myfp, unsigned char code[], funcp *entry) 
{
  int line = 1;
  int  c;
  int aux;

  unsigned char * vetor = malloc(1000);
  s_vct cdm = cria_vct(vetor);

  int * funcs = malloc(50 * sizeof(int));
  int func_atual = 0;
  
  while ((c = fgetc(myfp)) != EOF) 
  {
    switch (c) 
    {
      /* function */
      case 'f': 
      { 
        char c0;
        
        if (fscanf(myfp, "unction%c", &c0) != 1)
        {
          error("comando invalido", line);
        }        
        processa_function(funcs, &func_atual, &cdm);
        printf("function\n");
        break;
      }
      /* end */
      case 'e': 
      { 
        char c0;
        
        if (fscanf(myfp, "nd%c", &c0) != 1)
        {
          error("comando invalido", line);
        }        

        processa_end(&cdm);
        printf("end\n");
      
        break;
      }
      /* retorno incondicional */
      case 'r': 
      {  
        int idx0;
        char var0;
        
        if (fscanf(myfp, "et %c%d", &var0, &idx0) != 2) 
        {
          error("comando invalido", line);
        }
        
        processa_ret(var0, idx0, &cdm);
        printf("ret %c%d\n", var0, idx0);
        
        break;
      }
      /* retorno condicional */
      case 'z': 
      {
        int idx0, idx1;
        char var0, var1;
      
        if (fscanf(myfp, "ret %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4) 
        {
          error("comando invalido", line);
        }        

        processa_zret(var0, idx0, &cdm, var1, idx1);
        printf("zret %c%d %c%d\n", var0, idx0, var1, idx1);
        
        break;
      }
      /* atribuicao */
      case 'v': 
      {  
        int idx0;
        char var0 = c, c0;
        
        if (fscanf(myfp, "%d = %c",&idx0, &c0) != 2)
        {
          error("comando invalido",line);
        }
          
        if (c0 == 'c') 
        { /* call */
          int f, idx1;
          char var1;
          
          if (fscanf(myfp, "all %d %c%d\n", &f, &var1, &idx1) != 3)
          {
            error("comando invalido",line);
          }

          processa_call(var1, idx1, idx0, f, funcs, &cdm);
          printf("%c%d = call %d %c%d\n",var0, idx0, f, var1, idx1);
        }
        /* operacao aritmetica */
        else 
        { 
          int idx1, idx2;
          char var1 = c0, var2, op;
         
          if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
          {
            error("comando invalido", line);
          }          

          processa_op(idx0, var1, idx1, op, var2, idx2, &cdm);
          printf("%c%d = %c%d %c %c%d\n", var0, idx0, var1, idx1, op, var2, idx2);
        }
        
        break;
      }
      default: error("comando desconhecido", line);
    }
    
    line++;
    fscanf(myfp, " ");
  }

  // loop que escreve o codigo de maquina do arquivo no vetor final que armazena o codigo de maquina (code)
  for (int j = 0;j < cdm.tam; j++)
  {
    code[j] = cdm.vetor[j];
  }

  // calcula o endereco da ultima funcao no arquivo lbs e coloca como o endereco de entry
  unsigned char * p = &(code[funcs[func_atual - 1]]);
  *entry = p;  
}
