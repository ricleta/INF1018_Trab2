/*
  Rafael Paladini Meirelles 2111538 3WA 
  Ricardo Bastos Leta Vieira 2110526 3WA 
*/

#include <stdio.h>
#include <stdlib.h>
#include "processa.h"
#include<string.h>

typedef int (*funcp) (int x);
static void error (const char *msg, int line) {
  fprintf(stderr, "erro %s na linha %d\n", msg, line);
  exit(EXIT_FAILURE);
}

void gera_codigo (FILE *myfp, unsigned char code[], funcp *entry) {
  int line = 1;
  int  c;

  unsigned char * vetor = malloc(1000);
  s_vct cdm = cria_vct(vetor);

  int * funcs = malloc(50);
  int func_atual = 0;
  while ((c = fgetc(myfp)) != EOF) {
    switch (c) {
      case 'f': { /* function */
        char c0;
        if (fscanf(myfp, "unction%c", &c0) != 1)
          error("comando invalido", line);
        processa_function(&funcs, &func_atual, &cdm);
        printf("function\n");
        break;
      }
      case 'e': { /* end */
        char c0;
        if (fscanf(myfp, "nd%c", &c0) != 1)
          error("comando invalido", line);
        processa_end(&cdm);
        printf("end\n");
        break;
      }
      case 'r': {  /* retorno incondicional */
        int idx0;
        char var0;
        if (fscanf(myfp, "et %c%d", &var0, &idx0) != 2) 
          error("comando invalido", line);
        processa_ret(var0, idx0, &cdm);
        printf("ret %c%d\n", var0, idx0);
        break;
      }
      case 'z': {  /* retorno condicional */
        int idx0, idx1;
        char var0, var1;
        if (fscanf(myfp, "ret %c%d %c%d", &var0, &idx0, &var1, &idx1) != 4) 
          error("comando invalido", line);
        processa_zret(var0, idx0, &cdm, var1, idx1);
        printf("zret %c%d %c%d\n", var0, idx0, var1, idx1);
        break;
      }
      case 'v': {  /* atribuicao */
        int idx0;
        char var0 = c, c0;
        if (fscanf(myfp, "%d = %c",&idx0, &c0) != 2)
          error("comando invalido",line);

        if (c0 == 'c') { /* call */
          int f, idx1;
          char var1;
          if (fscanf(myfp, "all %d %c%d\n", &f, &var1, &idx1) != 3)
            error("comando invalido",line);
          processa_call(var1, idx1, idx0, f, funcs, &cdm);
          printf("%c%d = call %d %c%d\n",var0, idx0, f, var1, idx1);
        }
        else { /* operaÃ§Ã£o aritmÃ©tica */
          int idx1, idx2;
          char var1 = c0, var2, op;
          if (fscanf(myfp, "%d %c %c%d", &idx1, &op, &var2, &idx2) != 4)
            error("comando invalido", line);
          processa_op(idx0, var1, idx1, op, var2, idx2, &cdm);
          printf("%c%d = %c%d %c %c%d\n",
                var0, idx0, var1, idx1, op, var2, idx2);
        }
        break;
      }
      default: error("comando desconhecido", line);
    }
    line ++;
    fscanf(myfp, " ");
  }
  code = cdm.vetor;
  entry = (void *)(code + funcs[func_atual]);
}