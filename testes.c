#include <stdlib.h>
#include <stdio.h>

unsigned char * atribui(int var, int val)
{
  unsigned char p1, p2, p3, p4;
  unsigned char * cdm = malloc(5);
  unsigned char pre = 11 * 16;
  
  switch(var)
  {
    case 0:
      pre += 8;
    break;
    case 1:
      pre += 11;
    break;
    case 2:
      pre += 9;
    break;
    case 3:
      pre += 10;
    break;
    case 4:
      pre += 14;
    break;
    default:
      printf("Valor inválido para variável\n");
    break;
  }
  
  p1 = val % (256 * 256 * 256);
  p2 = (val % (256 * 256)) / (256);
  p3 = (val % 256) / 256;
  p4 = val / (256 * 256 * 256);


  cdm[0] = pre;
  cdm[1] = p1;
  cdm[2] = p2;
  cdm[3] = p3;
  cdm[4] = p4;
  
  return cdm;
}

unsigned char * processa_ret(char var, int id){
  unsigned char * vetor = malloc(3);
  switch(var){
    case 'v':{
      // Retorna variável
      switch (id){
        // v0
        case 0:{
          vetor[0] = (unsigned char)0x89;
          vetor[1] = (unsigned char)0xd8;
          break;
        }
        case 1:{
          vetor[0] = (unsigned char)0x44;
          vetor[1] = (unsigned char)0x89;
          vetor[2] = (unsigned char)0xe0;
          break;
        }
        case 2:{
          vetor[0] = (unsigned char)0x44;
          vetor[1] = (unsigned char)0x89;
          vetor[2] = (unsigned char)0xe8;
          break;
        }
        case 3:{
          vetor[0] = (unsigned char)0x44;
          vetor[1] = (unsigned char)0x89;
          vetor[2] = (unsigned char)0xf0;
          break;
        }
        case 4:{
          vetor[0] = (unsigned char)0x44;
          vetor[1] = (unsigned char)0x89;
          vetor[2] = (unsigned char)0xf8;
          break;
        }
      }
      break;
    }
    case 'p':{
      // Retorna parâmetro
      vetor[0] = (unsigned char)0x89;
      vetor[1] = (unsigned char)0xf8;
      break;
    }
    case '$':{
      // Retorna inteiro
      break;
    }
  }
  return vetor;
}
int main(void)
{
  int testes[6][2] = {{'v', 0}, {'v', 1}, {'v', 2}, {'v', 3}, {'v', 4}, {'p', 0}}; 

  for(int i=0; i < 6; i++)
  {
    unsigned char * linha = processa_ret(testes[i][0], testes[i][1]);  
    printf("Variável: %c%d Linha gerada: ", testes[i][0], testes[i][1]);
    for(int j=0; j < 3; j++)
    {
      printf("%02x ", linha[j]);
    }
    printf("\n");
  }
  return 0;
}