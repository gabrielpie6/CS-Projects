#include <stdio.h>
#define size 30

//Realiza ajustes conforme executado em sistema operacional Windows ou Linux
#ifdef _WIN32
    #include <windows.h>
    #define CLEAR "cls"
    char celula[] = {254, 0x00};
    void Delay(int seconds)
        {Sleep(seconds * 1000);}
#else
    #include <unistd.h>
    #define CLEAR "clear"
    char celula[] = {0xe2, 0x96, 0xa0, 0x00};
    void Delay(int seconds)
        {sleep(seconds);}
#endif

int Contagem(char *Ponteiro, int *lin, int *col);
void NovaGeracao(char *Ponteiro);

int main(int argc, char *argv[])
{
    int i, j, k;
    char Quadro[size][size];
    char *ptrQuadro = &Quadro[0][0];


    //Leitura do arquivo
    FILE *file = fopen(argv[1], "r");
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            fscanf(file, "%c\n", &Quadro[i][j]);
    fclose(file);


    //Processamento e Saída de valores
    for (k = 1; k <= atoi(argv[2]); k++)
    {
        //Cabeçalho
        system(CLEAR);
        printf("%49s", "Conway's Game of Life\n\e(0\x6c\e(B");
        for (i = 0; i < 60; i++)
            printf("\e(0\x71\e(B");
        printf("\e(0\x6b\e(B\n");

        for(i = 0; i < size; i++)
        {
            printf("\e[0m\e(0\x78\e(B");
            for(j = 0; j < size; j++)
                if (Quadro[i][j] == '1')
                    printf("\e[93m%s ", celula);
                else
                    printf("\e[90m%s ", " ");
            printf("\e[0m\e(0\x78\e(B");
            printf("\n");
        }
        
        //Rodapé
        printf("\e(0\x6d\e(B");
        for (i = 0; i < 60; i++)
            printf("\e(0\x71\e(B");
        printf("\e(0\x6a\e(B\n\e[0m\e[93m%54d \e[0mgeracao\n", k);
        NovaGeracao(&Quadro[0][0]);
        
        //Delay de 1 segundo:
        Delay(1);
    }
    
    return 0;
}


//Conta a quantidade de vizinhos vivos, respeitando os limites do quadro passado
int Contagem(char *Ponteiro, int *lin, int *col)
{
    int i, j;
    int contagem = 0;
    for (i = -1; i <= 1; i++)
        for (j = -1; j <= 1; j++)
            if ((0 <= *lin + i && *lin + i < size) && (0 <= *col + j && *col + j < size) && (*lin + i != *lin || *col + j != *col))
                if (*(Ponteiro + (*lin + i)*size + (*col + j)) == '1')
                    contagem++;

    return contagem;
}


// Processa uma nova geração sobrescrevendo a geração existente.
// Analisa a geração atual e gera uma matriz de vizinhos vivos relativos a cada célula, para somente
// então processar uma nova geração com base na matriz de vizinhos vivos. Caso contrário, os resultados serão divergentes.
void NovaGeracao(char *Ponteiro)
{
    int i, j, Vivos[size][size];
    int * pVivos = &Vivos[0][0];

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            *(pVivos + i*size + j) = Contagem(Ponteiro, &i, &j);

    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (*(pVivos + i*size + j) < 2 || *(pVivos + i*size + j) > 3)
                *(Ponteiro + i*size + j) = '0';
            else
                if (*(pVivos + i*size + j) == 3)
                    *(Ponteiro + i*size + j) = '1';
}