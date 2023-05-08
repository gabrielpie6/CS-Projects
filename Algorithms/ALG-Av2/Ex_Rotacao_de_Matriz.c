// 2) ROTAÇÃO DE MATRIZ
//    GABRIEL PIETSIAKI IZIDORO

#include <stdio.h>

void EscreveMatriz(int * M, int N);

void main()
{
    int N, i, j, aux;

    FILE *fptr = fopen("matriz_rotacao.txt", "r");
    fscanf(fptr, "%d", &N);
    
    //Leitura dos valores numéricos em arquivo
    int Matriz[N][N];
    for (i = 0; i < N; i++)
        for (j = 0; j < N; j++)
            fscanf(fptr, "%d", &Matriz[i][j]);
    fclose(fptr);

    EscreveMatriz(&Matriz[0][0], N);
}

void EscreveMatriz(int * M, int N)
{
    int i, j;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
            printf("%3d ", *(M + i * N + j));
        printf("\n");
    }
}

int * RotacionaMatriz(int * M, int N)
{
    int i, j, k, aux;

    for (i = N-1; i >= 0; i--)
    {
        for (j = 0; j < N; j++)
        {
            
        }
    }

    return M;
}