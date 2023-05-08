// 4) GOTAS NA JANELA
//    GABRIEL PIETSIAKI IZIDORO

// PROBLEMA: Resta implementar a soma de gotas.

#include <stdio.h>
#include <stdlib.h>
#define MAX_LIN 10
#define MAX_COL 5

typedef struct reg {
    int lin;
    int col;
    char type;
} Janela;

Janela * Leitura(FILE *fptr, int qtd);
void AtualizarJanela(Janela *gotas, int qtd);
int Contagem(Janela *gotas, int qtd);

void main()
{
    int qtd, passos, i;

    // Leitura e armazenamento dos valores por arquivo
    FILE *fptr = fopen("Gotas.txt", "r");
    fscanf(fptr, "%d", &qtd);
    Janela *gotas = Leitura(fptr, qtd);
    fscanf(fptr, "%d", &passos);
    fclose(fptr);

    
    // Repetição da simulação por quantidade de passos
    for (i = 0; i < passos; i++)
        AtualizarJanela(gotas, qtd);
    
    printf("Qtd. gotas restantes na janela: %d", Contagem(gotas, qtd));
}

Janela * Leitura(FILE *fptr, int qtd)
{
    int linha, coluna, i;
    char tipo;

    Janela *gotas = malloc(qtd * sizeof(Janela));
    for (i = 0; i < qtd; i++)
    {
        fscanf(fptr, "%d %d %c", &linha, &coluna, &tipo);
        if (linha < MAX_LIN && coluna < MAX_COL)
        {
            (gotas + i)->lin = linha;
            (gotas + i)->col = coluna;
            (gotas + i)->type = tipo;
        }
        else
            (gotas + i)->type = '0';
    }

    return gotas;
}

void AtualizarJanela(Janela *gotas, int qtd)
{
    int i;
    for (i = 0; i < qtd; i++)
    {
        if ((gotas + i)->type == 'G')
            (gotas + i)->lin++;
        else
            if ((gotas + i)->type == 'P')
                (gotas + i)->lin += 2;
    }
}

int Contagem(Janela *gotas, int qtd)
{
    int i, contagem = 0;
    for (i = 0; i < qtd; i++)
    {
        if ((gotas + i)->lin < MAX_LIN)
            contagem++;
    }

    return contagem;
}