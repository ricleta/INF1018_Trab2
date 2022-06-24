#include "auxiliares.h"

void processa_function(int ** funcs, int * func_atual, s_vct * cdm);
void processa_end(s_vct * cdm);
void processa_ret(char var, int id, s_vct * cdm);
void processa_zret(char var1, int id1, s_vct * cdm, char var2, int id2);
void processa_call(char varp, int idp, int id, int called, int * funcs, s_vct * cdm);
void processa_op(int id1, char var2, int id2, char op, char var3, int id3, s_vct * cdm);