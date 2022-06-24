#include <stdio.h>
#include "gera_codigo.h"

int main(int argc, char *argv[]) {
  FILE *fp;
  unsigned char code[300];
  funcp funcLBS;
  int res;
  /* Abre o arquivo para leitura */
  fp = fopen("novo_trab/teste0.txt", "r");
  /* Gera o codigo */
  gera_codigo(fp, code, &funcLBS);
  if (funcLBS == NULL) {
    printf("Erro na geracao\n");
  }
  /* Chama a função gerada */
  res = (*funcLBS)(0);
  printf("%d\n", res);
}