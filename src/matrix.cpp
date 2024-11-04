#include <iostream>
#include <stdlib.h>

#define UNROLL_SIZE 10

double** alocar_matriz(int n);
double** alocar_empty_matriz(int n);
void     print_matriz(double** m, int n);
void     desalocar_matriz(double** m, int n); 

int main(int argc, char* argv[]){

    char     tecnica = 'N';
    int      N = 1, rseed = 1337;
    double **A, **B, **C;

    // Verificando os parâmetros
    if(argc < 3){
        std::cout << "[-] Número incorreto de parâmetros." << std::endl;
        std::cout << "[-] exec <Tamanho> <Técnica> [<Random Seed>]" << std::endl;
        std::cout << "[-] <Técnica>:";
        std::cout << " [N] Normal, [I] Loop Interchange ou [U] Loop Unrolling" << std::endl;
        return 1;
    }

    // Lendo os parâmetros
    sscanf(argv[1], "%d", &N);
    sscanf(argv[2], "%c", &tecnica);
    if(argc >= 4) sscanf(argv[3], "%d", &rseed);

    // Iniciando parâmetro aleatório
    srand(rseed);

    A = alocar_matriz(N);
    B = alocar_matriz(N);
    C = alocar_empty_matriz(N);

    // Realizando as multiplicações
    if (tecnica == 'N' || tecnica == 'n'){
        
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int t = 0; t < N; t++)
                    C[i][j] += A[i][t] * B[t][j];

    } else if (tecnica == 'I' || tecnica == 'i') {

        for(int i = 0; i < N; i++)
            for(int t = 0; t < N; t++)
                for(int j = 0; j < N; j++)
                    C[i][j] += A[i][t] * B[t][j];

    } else if (tecnica == 'U' || tecnica == 'u') {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                for(int t = 0; t < N; t+= UNROLL_SIZE){
                    C[i][j] += A[i][t]   * B[t][j];
                    C[i][j] += A[i][t+1] * B[t+1][j];
                    C[i][j] += A[i][t+2] * B[t+2][j];
                    C[i][j] += A[i][t+3] * B[t+3][j];
                    C[i][j] += A[i][t+4] * B[t+4][j];
                    C[i][j] += A[i][t+5] * B[t+5][j];
                    C[i][j] += A[i][t+6] * B[t+6][j];
                    C[i][j] += A[i][t+7] * B[t+7][j];
                    C[i][j] += A[i][t+8] * B[t+8][j];
                    C[i][j] += A[i][t+9] * B[t+9][j];
                }
    }

    desalocar_matriz(A, N);
    desalocar_matriz(B, N);
    desalocar_matriz(C, N);
    return 0;
}

double** alocar_matriz(int n){
    double** m = (double**)  malloc(n * sizeof(double*)); 
    for(int i = 0; i < n; i++){
        m[i] = (double*) malloc(n * sizeof(double));
        for(int j = 0; j < n; j++)
            m[i][j] = rand()%1000;
    }

    return m;
}

double** alocar_empty_matriz(int n){
    double** m = (double**) malloc(n * sizeof(double*)); 
    for(int i = 0; i < n; i++){
        m[i] = (double*) malloc(n * sizeof(double));
    }

    return m;
}

void desalocar_matriz(double** m, int n){
    for(int i = 0; i < n; i++)
        free(m[i]);
    free(m);
}

void print_matriz(double** m, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            printf("%7.1lf ", m[i][j]);
        }
        printf("\n");
    }   
}