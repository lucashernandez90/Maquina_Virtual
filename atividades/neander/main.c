#include "neander.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Erro: Arquivo não especificado.\n");
    return 1;
  }

  executarNeander(argv[1]);
  return 0;
}
