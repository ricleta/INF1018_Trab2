#include <stdlib.h>

/*
  Rafael Paladini Meirelles 2111538 3WA 
  Ricardo Bastos Leta Vieira 2110526 3WA 
*/

#include <stdio.h>
#include "gera_codigo.h"

// trabalho fica aqui
/*
   0:   b8 01 00 00 00          mov    $0x1,%eax
   5:   bb 01 00 00 00          mov    $0x1,%ebx
   a:   b9 01 00 00 00          mov    $0x1,%ecx
   f:   ba 01 00 00 00          mov    $0x1,%edx
  14:   be 01 00 00 00          mov    $0x1,%esi
  19:   bf 01 00 00 00          mov    $0x1,%edi
*/

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
      pre += 15;
    break;
    default:
      printf("Valor inválido para variável\n");
    break;
  }
  
  p1 = val % (256 * 256 * 256);
  p2 = (val % (256 * 256)) / 256;
  p3 = (val % 256) / (256 * 256);
  p4 = val / (256 * 256 * 256);

  *cdm = pre;
  cdm++;
  
  *cdm = p1;
  cdm++;
  
  *cdm = p2;
  cdm++;
  
  *cdm = p3;
  cdm++;
  
  *cdm = p4;

  return cdm;
}