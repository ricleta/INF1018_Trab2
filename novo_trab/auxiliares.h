typedef struct vct{
  unsigned char * vetor;
  int tam;
} s_vct;
s_vct cria_vct(unsigned char * vetor);
void quebra_int(int inteiro, unsigned char bytes[4]);
void concatena (s_vct arr, unsigned char * arr2, int tam2);
int pos_pilha(int id);
void pilha_para_reg(int id, unsigned char * vetor);
void pilha_para_aux(int id, unsigned char * vetor);
void reg_para_pilha(int id, unsigned char * vetor);
void prologo( unsigned char * vetor);
void prep_ret (unsigned char * vetor);
void prep_call (unsigned char * vetor);
void pega_ret(unsigned char * vetor);
void ret(unsigned char * vetor);
void num_para_reg(int num, s_vct * arr);
void num_para_aux(int num, s_vct * arr);
void operation(char op, unsigned char * vetor);