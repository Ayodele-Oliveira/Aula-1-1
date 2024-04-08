#include <stdio.h>
#include <stdlib.h>


double *Levetor(char *nome, int *m){
  double *x;
  FILE *arquivo;
  int i;
  
  arquivo = fopen(nome, "r");
  fscanf(arquivo, "%d", m);
  printf ("m=%d\n",*m);

  x = malloc(*m*sizeof(double));
  for(i=0; i<m; i++);
  fscanf(arquivo, "%lf",&x[i]);
  return x;
}

void ImprimeVetor(double *x, int m){
  for (int i = 0; i < m; i++)
    printf("x[1%d]=%lfzn", i, x[i]);
}

int main(int argc, char **argv){
  double *x;
  int i, m;
  FILE *arquivo;
   x = Levetor(argv[1], &m);
  ImprimeVetor(x,m);
  return 0;
}


/*int i;
int *p;
printf(" tamanho %lu\n", sizeof(*p)); // como p é um ponteiro com 8 acessa 64
                                      // bits e só o conteúdo acessa 32bits.*/