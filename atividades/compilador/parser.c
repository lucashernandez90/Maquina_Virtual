#include "parser.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_MAX_LINHA 256
#define MAX_INSTRUCOES 256

Programa *analisar_arquivo(const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (!arquivo) return NULL;

    Programa *programa = malloc(sizeof(Programa));
    programa->instrucoes = malloc(MAX_INSTRUCOES * sizeof(Instrucao));
    programa->quantidade = 0;

    char linha[TAM_MAX_LINHA];
    while (fgets(linha, TAM_MAX_LINHA, arquivo)) {
        char *token = strtok(linha, " \n");
        if (!token) continue;

        Instrucao instrucao;
        strcpy(instrucao.operacao, token);

        token = strtok(NULL, " \n");
        instrucao.argumento = token ? atoi(token) : 0;

        programa->instrucoes[programa->quantidade++] = instrucao;
    }

    fclose(arquivo);
    return programa;
}

void liberar_programa(Programa *programa) {
    if (programa) {
        free(programa->instrucoes);
        free(programa);
    }
}