#include "gerador_asm.h"
#include <stdio.h>
#include <string.h>

void gerar_codigo_asm(Programa *programa, const char *arquivo_saida) {
    FILE *arquivo = fopen(arquivo_saida, "w");
    if (!arquivo) return;

    for (int i = 0; i < programa->quantidade; i++) {
        Instrucao instr = programa->instrucoes[i];
        fprintf(arquivo, "%s %02X\n", instr.operacao, instr.argumento);
    }

    fclose(arquivo);
}