/*
 * Sistema de Monitoramento de Temperatura
 * ----------------------------------------
 * O programa le um limite de temperatura definido pelo usuario e, em
 * seguida, realiza leituras sucessivas de temperatura. Sempre que 3
 * leituras CONSECUTIVAS ficarem acima do limite, o monitoramento e
 * encerrado automaticamente e um relatorio final e exibido.
 * Estruturas de repeticao utilizadas: while e do...while 
 */

#include <stdio.h>

#define MAX_CONSECUTIVAS 3

/*
 * Descarta os caracteres restantes no buffer de entrada ate encontrar
 * uma quebra de linha ou o fim do arquivo. E necessaria porque, quando
 * o usuario digita um valor nao numerico, o scanf("%f", ...) falha e
 * deixa esse texto invalido no buffer, o que causaria um laco infinito
 * de leituras invalidas se nao fosse limpo.
 */
void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta o caractere */
    }
}

int main(void) {
    float limite;
    float temperatura;
    int resultadoLeitura;

    int totalLeituras = 0;
    int qtdAcimaLimite = 0;
    int consecutivasAcima = 0;
    int primeiraLeitura = 1;

    float soma = 0.0f;
    float maior = 0.0f;
    float menor = 0.0f;

    /* 1 = encerrado por 3 leituras consecutivas acima do limite */
    int motivoEncerramento = 0;

    printf("=== SISTEMA DE MONITORAMENTO DE TEMPERATURA ===\n\n");

    /*
     * Validacao do limite de temperatura.
     * Usa-se do while porque o valor precisa ser solicitado pelo
     * menos uma vez, repetindo a solicitacao enquanto a entrada nao
     * for um numero valido.
     */
    do {
        printf("Informe o limite de temperatura (C): ");
        resultadoLeitura = scanf("%f", &limite);
        limparBufferEntrada();

        if (resultadoLeitura == 0) {
            printf("Entrada invalida! Digite um valor numerico para o limite.\n\n");
        }
    } while (resultadoLeitura == 0);

    if (resultadoLeitura != 1) {
        printf("\nFim inesperado da entrada de dados. Encerrando o programa.\n");
        return 1;
    }

    printf("\nLimite de temperatura definido: %.2f C\n\n", limite);

    /*
     * Loop principal de monitoramento.
     * Usa-se while porque a quantidade de leituras nao e conhecida
     * previamente: o monitoramento continua enquanto o numero de
     * temperaturas consecutivas acima do limite for menor que 3.
     */
    while (consecutivasAcima < MAX_CONSECUTIVAS) {

        /*
         * Validacao de cada leitura de temperatura.
         * Novamente do...while, pois a leitura precisa ser solicitada
         * ao menos uma vez e repetida enquanto o valor digitado nao
         * for numerico.
         */
        do {
            printf("Temperatura #%d: ", totalLeituras + 1);
            resultadoLeitura = scanf("%f", &temperatura);
            limparBufferEntrada();

            if (resultadoLeitura == 0) {
                printf("Entrada invalida! Digite um valor numerico para a temperatura.\n\n");
            }
        } while (resultadoLeitura == 0);

        if (resultadoLeitura != 1) {
            printf("\nFim inesperado da entrada de dados. Encerrando o programa.\n");
            return 1;
        }

        totalLeituras++;
        soma += temperatura;

        if (primeiraLeitura) {
            maior = temperatura;
            menor = temperatura;
            primeiraLeitura = 0;
        } else {
            if (temperatura > maior) {
                maior = temperatura;
            }
            if (temperatura < menor) {
                menor = temperatura;
            }
        }

        if (temperatura > limite) {
            /* Temperatura acima do limite: soma mais uma consecutiva */
            consecutivasAcima++;
            qtdAcimaLimite++;
            printf(">> ACIMA do limite! (%d leitura(s) consecutiva(s) acima do limite)\n\n", consecutivasAcima);
        } else {
            /* Temperatura no limite ou abaixo dele: quebra a sequencia */
            consecutivasAcima = 0;
            printf(">> Dentro do limite.\n\n");
        }
    }

    motivoEncerramento = 1;

    /* Relatorio final do monitoramento */
    printf("\n=== RELATORIO FINAL ===\n");
    printf("Quantidade de temperaturas lidas : %d\n", totalLeituras);

    if (totalLeituras > 0) {
        /* Divisao por zero nao ocorre aqui: o loop so termina apos pelo
           menos MAX_CONSECUTIVAS leituras validas, mas a checagem e
           mantida por seguranca. */
        printf("Media das temperaturas          : %.2f C\n", soma / totalLeituras);
        printf("Maior temperatura                : %.2f C\n", maior);
        printf("Menor temperatura                : %.2f C\n", menor);
        printf("Quantidade acima do limite       : %d\n", qtdAcimaLimite);
        printf("Percentual acima do limite       : %.2f%%\n", (qtdAcimaLimite / (float) totalLeituras) * 100.0f);
    } else {
        printf("Nenhuma temperatura foi registrada.\n");
    }

    printf("Motivo do encerramento           : ");
    if (motivoEncerramento == 1) {
        printf("%d temperaturas consecutivas acima do limite.\n", MAX_CONSECUTIVAS);
    }

    return 0;
}
