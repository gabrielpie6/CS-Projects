#include <stdio.h>
#include <stdlib.h>
#define n 15

typedef struct reg {
    int conteudo;
    int lin;
    int col;
    struct reg *prox;
} celula;

celula * Leitura_Condensada(FILE *file);
void Escrita_Condensada(celula *inicio);
int Busca_Encadeada(celula *inicio, int linha, int coluna);
celula * Soma_Condensada(celula *A, celula *B);
celula * Soma_Alternativa(celula *A, celula *B);
celula * Mutiplicacao_Condensada(celula *A, celula *B);
int Soma_AreaHachurada (celula *A);

void Desalocar_Lista(celula * inicio);
void Cabecalho();
void Pause();

void main()
{
    celula *listaA, *listaB, *lista, *listaSOMA, *listaMULT;
    int operacao, valor;

    //Leitura das matrizes
    FILE *file = fopen("Matrizes.txt", "r");
    listaA = Leitura_Condensada(file);
    listaB = Leitura_Condensada(file);
    fclose(file);


    //MENU DE OPERACOES
    Cabecalho();
    printf("\n\e[33m1\e[0m. SOMA DAS MATRIZES\n\e[33m2\e[0m. MULTIPLICACAO\n\e[33m3\e[0m. SOMA DOS ELEMENTOS ABAIXO DA DIAGONAL PRINCIPAL\n\e[33m4\e[0m. FINALIZAR.\n\n>> Digite a operacao desejada: ");
    scanf("%d", &operacao);

    while (operacao != 4)
    {
        switch (operacao)
        {
            case 1:
            {
                lista = Soma_Condensada(listaA, listaB);
                Escrita_Condensada(lista);
                Desalocar_Lista(lista);
                Pause();
                break;
            }
            case 2:
            {
                Cabecalho();
                printf("\n2. MULTIPLICACAO\n   \e[33m1\e[0m. A x B\n   \e[33m2\e[0m. B x A\n\n>> Digite a operacao desejada: ");
                scanf("%d", &operacao);

                if (operacao == 1)
                    lista = Mutiplicacao_Condensada(listaA, listaB);
                else
                    lista = Mutiplicacao_Condensada(listaB, listaA);
                Escrita_Condensada(lista);
                Desalocar_Lista(lista);
                Pause();
                break;
            }
            case 3:
            {
                Cabecalho();
                printf("\n3. SOMA DOS ELEMENTOS ABAIXO DA DIAGONAL PRINCIPAL\n   \e[33m1\e[0m. Area hachurada de A\n   \e[33m2\e[0m. Area hachurada de B\n\n>> Digite a operacao desejada: ");
                scanf("%d", &operacao);

                if (operacao == 1)
                    valor = Soma_AreaHachurada(listaA);
                else
                    valor = Soma_AreaHachurada(listaB);
                printf("\n\e[33mResultado: %d\e[0m", valor);
                Pause();
                break;
            }
            default:
            {
                printf("\n\e[1mERRO: codigo de acao invalido!\e[0m");
                Pause();
                break;
            }
        }
        Cabecalho();
        printf("\n\e[33m1\e[0m. SOMA DAS MATRIZES\n\e[33m2\e[0m. MULTIPLICACAO\n\e[33m3\e[0m. SOMA DOS ELEMENTOS ABAIXO DA DIAGONAL PRINCIPAL\n\e[33m4\e[0m. FINALIZAR.\n\n>> Digite a operacao desejada: ");
        scanf("%d", &operacao);
    }
}

// Realiza a leitura de uma matriz de elementos numéricos INTEIROS, armazena somente os elementos não-nulos
// em células de uma lista simplesmente encadeada e então a retorna.
celula * Leitura_Condensada(FILE *file)
{
    celula *inicio;
    celula *aux;
    int i, j, valor;

    //Célula inicial provisória.
    aux = malloc(sizeof(celula));
    inicio = aux;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            fscanf(file, "%d ", &valor);
            if (valor != 0)
            {
                aux->prox = malloc(sizeof(celula));
                aux = aux->prox;
                aux->conteudo = valor;
                aux->lin = i;
                aux->col = j;
                aux->prox = NULL;
            }
        }
    aux = inicio;
    inicio = inicio->prox;
    free(aux);

    return inicio;
}

// Realiza a escrita de uma matriz condensada armazenada em uma lista simplesmente encadeada.
void Escrita_Condensada(celula *inicio)
{
    int i, j;

    //Dados da lista condensada
    celula *p;
    printf("\n\e[33m DADOS DA LISTA CONDENSADA \n      val   lin   col\e[0m\n");
    for (p = inicio; p != NULL; p = p->prox)
        printf("%8d%6d%6d\n", p->conteudo, p->lin, p->col);

    //Representação matricial
    printf("\n      \e[33mFORMA MATRICIAL \e[0m\n");
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            if (inicio != NULL && inicio->lin == i && inicio->col == j)
            {
                printf("%4d ", inicio->conteudo);
                inicio = inicio->prox;
            }
            else
                printf("%5s", "0 ");
        printf("\n");
    }
}

// Realiza a busca de um elemento específico com base em seus índices e retorna seu conteúdo.
int Busca_Encadeada(celula *inicio, int linha, int coluna)
{
    int resultado = 0;
    while (inicio != NULL && (inicio->lin != linha || inicio->col != coluna))
    {
        inicio = inicio->prox;
    }
    if (inicio != NULL)
        resultado = inicio->conteudo;
    
    return resultado;
}

// Realiza a soma de duas matrizes condensadas armazenadas em duas listas simplesmente encadeadas e retorna
// a matriz condensada resultante também armazenada em uma lista simplesmente encadeada.
celula * Soma_Condensada(celula *A, celula *B)
{
    celula *C, *aux, *fimC, *fimA = A, *fimB = B;
    int posicaoA, posicaoB, Soma, linha, coluna;

    //Celula temporária
    C = malloc(sizeof(celula));
    C->conteudo = -1;
    C->col = -1;
    C->lin = -1;
    C->prox = NULL;

    fimC = C;
    while (fimA != NULL || fimB != NULL)
    {
        if (fimA != NULL)
            posicaoA = fimA->lin * n + fimA->col;
        else
            posicaoA = posicaoB + 1;

        if (fimB != NULL)
            posicaoB = fimB->lin * n + fimB->col;
        else
            posicaoB = posicaoA + 1;

        if (posicaoA < posicaoB)
        {
            //Caso A sozinho:
            Soma = fimA->conteudo;
            linha = fimA->lin;
            coluna = fimA->col;

            fimA = fimA->prox;
        } else
            if (posicaoA > posicaoB)
            {
                //Caso B sozinho:
                Soma = fimB->conteudo;
                linha = fimB->lin;
                coluna = fimB->col;

                fimB = fimB->prox;
            } else
            {
                //Caso A e B na mesma posicao:
                Soma = fimA->conteudo + fimB->conteudo;
                linha = fimA->lin;
                coluna = fimA->col;

                fimA = fimA->prox;
                fimB = fimB->prox;
            }

        if (Soma != 0)
        {
            aux = malloc(sizeof(celula));
            aux->conteudo = Soma;
            aux->prox = NULL;
            aux->lin = linha;
            aux->col = coluna;

            fimC->prox = aux;
            fimC = fimC->prox;
        }
    }
    aux = C;
    C = C->prox;
    free(aux);

    return C;
}

// Função semelhante a Soma_Condensada(), porém utilizando um método MENOS EFICIENTE quando aplicado em
// matrizes com maior quantidade de elementos nulos.
celula * Soma_Alternativa(celula *A, celula *B)
{
    celula *inicio, *aux;
    int i, j, soma;

    //Célula inicial provisória.
    aux = malloc(sizeof(celula));
    inicio = aux;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            soma = 0;
            if (A != NULL && A->lin == i && A->col == j)
            {
                soma += A->conteudo;
                A = A->prox;
            }
            if (B != NULL && B->lin == i && B->col == j)
            {
                soma += B->conteudo;
                B = B->prox;
            }

            if (soma != 0)
            {
                aux->prox = malloc(sizeof(celula));
                aux = aux->prox;
                aux->conteudo = soma;
                aux->lin = i;
                aux->col = j;
                aux->prox = NULL;
            }
        }
    }
    aux = inicio->prox;
    free(inicio);
    inicio = aux;

    return inicio;    
}

// Realiza a multiplicação de duas matrizes condensadas armazenadas em duas listas simplesmente encadeadas e
// retorna a matriz condensada resultante obtida em uma nova lista também simplesmente encadeada.
celula * Mutiplicacao_Condensada(celula *A, celula *B)
{
    celula *inicio, *aux;
    int i, j, k, soma;

    //Célula inicial provisória.
    aux = malloc(sizeof(celula));
    inicio = aux;
    
    //NÚCLEO DA MULTIPLICAÇÃO DE MATRIZES
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            soma = 0;
            for (k = 0; k < n; k++)
                soma += Busca_Encadeada(A, i, k) * Busca_Encadeada(B, k, j);
            if (soma != 0)
            {
                aux->prox = malloc(sizeof(celula));
                aux = aux->prox;
                aux->conteudo = soma;
                aux->lin = i;
                aux->col = j;
                aux->prox = NULL;
            }
        }
    }

    aux = inicio->prox;
    free(inicio);
    inicio = aux;

    return inicio;
}

// Realiza a soma de todos os elementos ESTRITAMENTE ABAIXO da diagonal principal da matriz desejada e então
// retorna o valor INTEIRO.
int Soma_AreaHachurada(celula *A)
{
    int soma = 0;
    while (A != NULL)
    {
        if ((1 <= A->lin && A->lin < n) && (0 <= A->col && A->col < A->lin))
            soma += A->conteudo;
        A = A->prox;
    }

    return soma;
}

// Desaloca todas as células de uma dada lista simplesmente encadeada
void Desalocar_Lista(celula * inicio)
{
    celula *aux;
    while (inicio != NULL)
    {
        aux = inicio;
        inicio = inicio->prox;
        free(aux);
    }
}

void Cabecalho()
{
    printf("\e[H\e[2J%33s\n%34s", "MATRIZ CONDENSADA", "MENU DE OPERACOES\n");
    for (int i = 0; i < 50; i++)
        printf("\e(0\x71\e(B");
}

void Pause()
{
    int v;
    printf("\nPressione 0 para voltar ao menu de operacoes.\n");
    scanf("%d", &v);
}