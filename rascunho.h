void quebra_int(int inteiro, unsigned char bytes[4]);
void processa_ret(char var, int id, unsigned char * vetor);
void processa_zret(char var1, int id1, char var2, int id2, unsigned char * vetor);
unsigned char * aloca_variavel(int n, char var, int id);
void guarda_pilha(unsigned char * vetor);
void tira_pilha(unsigned char * vetor);
void concatena (unsigned char * arr1, int tam1, unsigned char * arr2, int tam2);