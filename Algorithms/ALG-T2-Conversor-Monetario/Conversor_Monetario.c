#include <stdio.h>
#include <math.h>

//
//  Caso haja problema com a função round(): incluir argumento "-lm" no comando de
//  compilação, pois <math.h> não é parte da standard C library e precisa ser especificada.
//  Ex.: "gcc Conversor_Monetario.c -lm"
//

int * Separador_Base10(int num);
void Escrita_Extenso(int a, int b, int c);
void main()
{
    float valor;
    int numero, inteiro, decimal;
    int i, j;
    int *casas;


    //Cabeçalho
    printf("\e[H\e[2J\n%41s\n", "NUMERO POR EXTENSO");
    for (i = 0; i < 65; i++)
        printf("\e(0\x71\e(B");
    printf("\nDigite um numero com ate 4 casas inteiras e ate 2 casas decimais.\n");
    printf(">> Ex.: 9999 ou 9999.99 ou .99\n");


    //Leitura inicial de um número
    printf("\nR$ ");
    scanf("%f", &valor);
    
    while (valor != 0)
    {
        //Obtém as casas em múltiplos de base 10 do número em análise
        numero = round(valor * 100.0);
        inteiro = numero / 100;
        decimal = numero % 100;
        casas = Separador_Base10(numero);
        printf(">> ");


        //Obtém número inteiro escrito por extenso (quando existe)
        if (inteiro != 0)
        {
            if (casas[0] != 0)
            {
                if (casas[0] != 1)
                {
                    Escrita_Extenso(0, 0, casas[0]);
                    printf(" ");
                }
                printf("mil");
                if (casas[1] != 0 || casas[2] != 0 || casas[3] != 0)
                    printf(" e ");
            }
            Escrita_Extenso(casas[1], casas[2], casas[3]);
            if (inteiro == 1)
                printf(" real");
            else
                printf(" reais");
            
            //Realiza a junção da escrita inteira com a decimal (quando existe)
            if (decimal != 0)
                printf(" e ");
        }

        //Obtém número relativo à parte fracionada escrito por extenso (quando existe)
        if (decimal != 0)
        {
            Escrita_Extenso(0, casas[4], casas[5]);
            printf(" centavo");
            if (decimal != 1)
                printf("s");
        }
        
        
        //Nova Leitura
        printf("\nR$ ");
        scanf("%f", &valor);
    }
}

//Decompõe um número em múltiplos de base 10 e retorna um ponteiro para vetor.
int * Separador_Base10(int num)
{
    static int casas[6];
    int i;
    int restos = num;
    int fator = 1000 * 100;
    for (i = 0; i < 6; i++)
    {
        casas[i] = restos / fator;
        restos = restos % fator;
        fator = fator / 10;
    }
    
    return &casas[0];
}

//Escreve o número recebido por extenso, seguindo a seguinte ordem de checagem para evitar inconsistências e conjunções desconexas:
//não-nulo -> exceção: cem (a, b, c) = (1, 0, 0) -> exceção: dezenas = 1 (avalia separadamente) -> necessidade de nova conjunção 
void Escrita_Extenso(int a, int b, int c)
{
    int i;
    int casas[] = {a, b, c};
    char *def[][9] = 
    {
        {"um", "dois", "tres", "quatro", "cinco", "seis", "sete", "oito", "nove"},
        {"dez", "vinte", "trinta", "quarenta", "cinquenta", "sessenta", "setenta", "oitenta", "noventa"},
        {"cento", "duzentos", "trezentos", "quatrocentos", "quinhentos", "seiscentos", "setecentos", "oitocentos", "novecentos"}
    };
    char *dezena[] = {"dez", "onze", "doze", "treze", "quatorze", "quinze", "dezesseis", "dezessete", "dezoito", "dezenove"};

    if (a != 0 || b != 0 || c != 0)
        if (a == 1 && b == 0 && c == 0)
            printf("cem");
        else
            for (i = 0; i < 3; i++)
                if (casas[1] != 1 || i != 2)
                {
                    if ((i == 1 && casas[i] != 0 && casas[i-1] != 0) || (i == 2 && casas[i] != 0 && (casas[i-1] != 0 || casas[i-2] != 0)))
                        printf(" e ");
                    if (i == 1 && casas[i] == 1)
                        printf("%s", dezena[casas[2]]);
                    else
                        if (casas[i] != 0)
                            printf("%s", def[2-i][casas[i]-1]);
                }
}