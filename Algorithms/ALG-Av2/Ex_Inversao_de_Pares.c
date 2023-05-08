// 4) INVERSAO DE PARES DE VALORES
//    GABRIEL PIETSIAKI IZIDORO

//  Obs.: Como está sendo inserido no início, a ordem dos elementos pela inserção
//        deve ser invertida
//  Sugestão de entrada:
//  6
//  6 5 4 3 2 1

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node *next;
};
typedef struct Node ListNode;

void InsereInicio(ListNode **ini, int val);
void EscreveLista(ListNode *ini);
ListNode * Inverte_Pares(ListNode **inicio, int qtd);
void main()
{
    int i, qtd, valor;

    ListNode *inicio, *aux;

    // Alocação de uma célula temporária para inicialização da lista
    inicio = malloc(sizeof(ListNode));
    inicio->next = NULL;
    inicio->val = -1;

    // Leitura da Lista por entrada manual
    printf("Quantidade de itens: ");
    scanf("%d", &qtd);
    for (i = 0; i < qtd; i++)
    {
        printf("Digite um elemento: ");
        scanf("%d", &valor);
        InsereInicio(&inicio, valor);

        // Remoção da célula temporária criada
        if (i == 0)
        {
            aux = inicio->next;
            inicio->next = NULL;
            free(aux);
        }
    }
    
    // printf("\nLista lida: ");
    // EscreveLista(inicio);

    inicio = Inverte_Pares(&inicio, qtd);

    printf("\nLista processada: ");
    EscreveLista(inicio);
}

void InsereInicio(ListNode **ini, int val)
{
    ListNode *aux;
    aux  = malloc(sizeof(ListNode));
    aux->val = val;
    aux->next = (*ini);
    (*ini) = aux;
}

void EscreveLista(ListNode *ini)
{
    ListNode *p;
    printf("\nConteudo da lista: ");
    for (p = ini; p != NULL; p = p->next)
        printf("%d ", p->val);
}

ListNode * Inverte_Pares(ListNode **inicio, int qtd)
{
    ListNode *aux, *cabeca, *anterior;
    int i;
    
    // Inversão dos pares de valores
    if (qtd > 1)
    {
        aux = *inicio;
        *inicio = (*inicio)->next;
        aux->next = (*inicio)->next;
        (*inicio)->next = aux;

        if (qtd > 2)
        {
            anterior = aux;
            cabeca = anterior->next;
            for (i = 1; i < qtd/2; i++)
            {
                aux = cabeca->next;
                cabeca->next = aux->next;
                aux->next = cabeca;

                anterior->next = aux;
                anterior = cabeca;
                cabeca = cabeca->next;
            }
        }
    }

    return *inicio;
}