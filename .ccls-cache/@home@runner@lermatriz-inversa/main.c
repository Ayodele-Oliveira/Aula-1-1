#include <stdio.h>
#include <stdlib.h>

double **LeMatriz(char *nome, int *m, int *n) {
  double **x;
  int i, j;
  FILE *arquivo;

  arquivo = fopen(nome, "r");
  fscanf(arquivo, "%d", m);
  fscanf(arquivo, "%d", n);
  printf("m=%d n=%d\n", *m, *n);

  x = malloc(*m * sizeof(double *));

  for (i = 0; i < *m; i++)
    x[i] = malloc(*n * sizeof(double));

  for (i = 0; i < *m; i++)
    for (j = 0; j < *n; j++)
      fscanf(arquivo, "%lf\n", &x[i][j]);

  return x;
}

void TrocaLinhasFundamental(double **x, int k, int l, int m, int n) {
  double temp;
  int i;
  for (i = 0; i < n; i++) {
    temp = x[k][i];
    x[k][i] = x[l][i];
    x[l][i] = temp;
  }
}

void TrocaLinhasENEM(double **x, int m, int n, int k, int l) {
  double *temp;

  temp = malloc(n * sizeof(double));
  memcpy(temp, x[k], n * sizeof(double));
  memcpy(x[k], x[l], n * sizeof(double));
  memcpy(x[l], temp, n * sizeof(double));
}

void TrocaLinhas(double **x, int k, int l) {
  double *temp;
  temp = x[k];
  x[k] = x[l];
  x[l] = temp;
  // trabalhamos com as linhas da matriz sendo um vetor independente.
}

void ImprimeMatriz(double **x, int m, int n) {
  int i, j;

  for (i = 0; i < m; i++)
    for (j = 0; j < n; j++) {
      printf("%.1lf ", x[i][j]);
    }
}

/*double **Transposta(double **x, int m, int n){
  int i, j;
  double **xt;

  xt = malloc(n*sizeof(double *));
  for (i=0; i <n; i++)
    xt[i] = malloc(m*sizeof(double));

  for(i=0; i<n;i++)
    for(j=0; j<m;j++)
      xt[i][j] = x[j][i];
  return xt;
}*/

double *EliminaGauss(double **M, int m, int n) {
  double *raiz;
  double pivot, lambda;
  int i, j, k, l, soma;

  raiz = malloc(m * sizeof(double));
  for (k = 0; k < m - 1; k++) {
    pivot = M[k][k];
    l = k + 1;
    if (pivot == 0) {
      do {
        if (M[l][k] != 0) {
          TrocaLinhas(M, l, k);
          pivot = M[k][l];
        }
        l++;
      } while ((pivot == 0) && (l < m));
    }
    // Se o pivot continua zerado após a procura por um novo pivot que seja
    // diferente de zero;

    if (pivot == 0) {
      printf("\nO sistema de equações não possui soluções!\n");
      return raiz;
    }

    for (j = 1; j < m; j++) {
      lambda = M[j][0];
      for (i = 0; i < n; i++) {
        M[j][i] += -M[k][i] / pivot * lambda;
      }
    }
  }
  ImprimeMatriz(M, m, n);
  // Fazendo o cálculp inverso

  for (i = m - 2; i >= 0; i--) {
    soma = 0;
    for (j = m - 1; j > i; j--) {
      soma += raiz[j] * M[i][j];
    }
    raiz[i] = (M[i][n - 1] - soma) / M[i][i];
  }

  /*raiz[m - 1] = M[m - 1][n - 1] / M[m - 1][m - 1];
  for (i = m - 2; i >= 0; i--) {
    raiz[i] = (M[i][n - 1] - M[i][m - 1] * raiz[i + 1]) / M[i][i];
  }*/

  for (i = 0; i < m; i++) {
    printf("\nraiz[%d] = %.1lf\n", i, raiz[i]);
  }
  return raiz;
}

int main(int argc, char **argv) {
  double **x, **xt, *solucao;
  int i, m, n;
  FILE *arquivo;

  x = LeMatriz(argv[1], &m, &n);
  // memcpy(xt,x,n*sizeof(double)) alocar o xt e fazer o for
  // xt = Transposta(x,m,n);
  ImprimeMatriz(x, m, n);
  // printf("\nTransposta\n");
  // ImprimeMatriz(xt,m,n);

  solucao = EliminaGauss(x, m, n);
  return 0;
}

/*int i;
int *p;
printf(" tamanho %lu\n", sizeof(*p)); // como p é um ponteiro com 8 acessa 64
                                      // bits e só o conteúdo acessa 32bits.*/