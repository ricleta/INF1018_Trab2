#include <stdlib.h>
#include <stdio.h>

unsigned char * atribui(int var, int val)
{
  int p1, p2, p3, p4;
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
  
  p1 = val & 0x000000ff;
  p2 = val & 0x0000ff00;
  p3 = val & 0x00ff0000;
  p4 = val & 0xff000000;

  cdm[0] = pre;
  cdm[1] = p1;
  cdm[2] = p2;
  cdm[3] = p3;
  cdm[4] = p4;
  
  return cdm;
}


int main(void)
{
  int testes[6][2] = {{0, 1}, {1, 2}, {2, 257}, {3, 1193046}, {4, 2147483647}, {0, 11206861}}; 

  for(int i=0; i < 6; i++)
  {
    unsigned char * linha = atribui(testes[i][0], testes[i][1]);  
    printf("Variável: %d Valor: %d Linha gerada: ", testes[i][0], testes[i][1]);
    for(int j=0; j < 5; j++)
    {
      printf("%02x ", linha[j]);
    }
    printf("\n");
  }
  return 0;
}