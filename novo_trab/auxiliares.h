void quebra_int(int inteiro, unsigned char bytes[4]);
void concatena (unsigned char * arr1, int * tam1, unsigned char * arr2, int tam2);
int pos_pilha(int id);
void pilha_para_reg(int id, unsigned char * vetor);
void reg_para_pilha(int id, unsigned char * vetor);
void prologo( unsigned char * vetor);
void prep_ret (unsigned char * vetor);
void ret(unsigned char * vetor);
typedef struct vct{
  unsigned char * vetor;
  int tam;
} s_vct;
s_vct cria_vct(unsigned char * vetor);