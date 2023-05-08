#include <stdio.h>

void main()
{
    int numero;
    printf("Digite um numero: ");
    scanf("%d", &numero);

    //Função Casas Decimais
    int casas[4], i;
    int restos = numero;
    int fator = 1000;
    for (i = 0; i < 4; i++)
    {
        casas[i] = restos / fator;
        restos = restos % fator;
        fator = fator / 10;
    }

    //escrever os milhares
    char *unidades[] = {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"};
    char *centenas[] = {"cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"};
    char *dezenas[] = {"dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"};
    char *subdez[] = {"onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};

    if (casas[0] != 0)
    {
        if (casas[0] != 1)
            printf("%s ", unidades[casas[0] - 1]);
        printf("mil ");
    }

    //escrever centena
    if (casas[1] != 0)
        printf("%s ", centenas[casas[1] - 1]);

    //escrever dezena
    if (casas[2] != 0)
    {
        if (casas[2] == 1 && casas[3] != 0)
            printf("%s ", subdez[casas[3] - 1]);
        else
            printf("%s ", dezenas[casas[2] - 1]);

    }

    //escreve unidade
    if (casas[3] != 0 && casas[2] != 1)
        printf("%s ", unidades[casas[3] - 1]);
}