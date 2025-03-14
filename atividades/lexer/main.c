#include "Lexer.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <arquivo_de_entrada>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror("Erro ao abrir o arquivo");
        return EXIT_FAILURE;
    }

    interpretar(input);
    fclose(input);
    return EXIT_SUCCESS;
}