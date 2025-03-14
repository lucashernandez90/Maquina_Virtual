#include "Lexer.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

static int lookahead;
static FILE *source;
static int memoria[256] = {0}; 
static int acumulador = 0;

Token next_token() {
    while (isspace(lookahead) || lookahead == ',')
        lookahead = fgetc(source);

    if (isalpha(lookahead)) {
        char buffer[32];
        int i = 0;
        while (isalpha(lookahead) && i < 31) {
            buffer[i++] = lookahead;
            lookahead = fgetc(source);
        }
        buffer[i] = '\0';

        if (strcmp(buffer, "DATA") == 0) return (Token){TOKEN_DATA, 0, ""};
        if (strcmp(buffer, "END") == 0) return (Token){TOKEN_END, 0, ""};
        if (strcmp(buffer, "CODE") == 0) return (Token){TOKEN_CODE, 0, ""};
        if (strcmp(buffer, "LDA") == 0) return (Token){TOKEN_LDA, 0, ""};
        if (strcmp(buffer, "ADD") == 0) return (Token){TOKEN_ADD, 0, ""};
        if (strcmp(buffer, "SUB") == 0) return (Token){TOKEN_SUB, 0, ""};
        if (strcmp(buffer, "MUL") == 0) return (Token){TOKEN_MUL, 0, ""};
        if (strcmp(buffer, "DIV") == 0) return (Token){TOKEN_DIV, 0, ""};

        Token t = {TOKEN_IDENT, 0, ""};
        strncpy(t.ident, buffer, 31);
        return t;
    }

    if (isdigit(lookahead)) {
        int value = 0;
        while (isdigit(lookahead)) {
            value = value * 10 + (lookahead - '0');
            lookahead = fgetc(source);
        }
        return (Token){TOKEN_INT, value, ""};
    }

    if (lookahead == ';') {
        lookahead = fgetc(source);
        return next_token();
    }

    if (lookahead == EOF)
        return (Token){TOKEN_EOF, 0, ""};

    fprintf(stderr, "Erro: Caractere inesperado: %c\n", lookahead);
    exit(EXIT_FAILURE);
}

void interpretar(FILE *input) {
    source = input;
    lookahead = fgetc(source);
    Token token;
    int index;

    while (1) {
        token = next_token();
        switch (token.type) {
            case TOKEN_DATA:
                while ((token = next_token()).type == TOKEN_INT) {
                    index = token.value; 
                    token = next_token();
                    if (token.type != TOKEN_INT) {
                        fprintf(stderr, "Erro: Esperado valor para DATA\n");
                        exit(EXIT_FAILURE);
                    }
                    memoria[index] = token.value;
                }
                break;
            case TOKEN_CODE:
                while (1) {
                    token = next_token();
                    if (token.type == TOKEN_END) break;
                    if (token.type == TOKEN_LDA) {
                        token = next_token();
                        acumulador = memoria[token.value];
                    } else if (token.type == TOKEN_ADD) {
                        token = next_token();
                        acumulador += memoria[token.value];
                    } else if (token.type == TOKEN_SUB) {
                        token = next_token();
                        acumulador -= memoria[token.value];
                    } else if (token.type == TOKEN_MUL) {
                        token = next_token();
                        acumulador *= memoria[token.value];
                    } else if (token.type == TOKEN_DIV) {
                        token = next_token();
                        if (memoria[token.value] == 0) {
                            printf("Aviso: Divisao por zero no indice %d! Valor: 0\n", token.value);
                            memoria[token.value] = 1;
                        }
                        acumulador /= memoria[token.value];
                    }
                }
                break;
            case TOKEN_END:
                printf("Resultado final: %d\n", acumulador);
                return;
            case TOKEN_EOF:
                return;
            default:
                fprintf(stderr, "Erro: Token inválido\n");
                exit(EXIT_FAILURE);
        }
    }
}
