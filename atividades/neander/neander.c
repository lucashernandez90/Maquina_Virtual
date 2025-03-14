#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#define STA 0x10
#define LDA 0x20
#define ADD 0x30
#define NOT 0x60
#define JMP 0x80
#define JN 0x90
#define JZ 0xA0
#define HLT 0xF0

int main(int argc, char **argv) {
  (void)argc; // Evita warning de parâmetro não utilizado

  if (argc < 2) {
    printf("Erro: Arquivo não especificado.\n");
    return 1;
  }

  FILE *file = fopen(argv[1], "rb");
  if (!file) {
    printf("Erro ao abrir arquivo.\n");
    return 1;
  }

  uint8_t bytes[256] = {0};
  uint8_t byte = 0;
  int getByte = 0;
  uint32_t memID = 0;
  uint8_t ac = 0, pc = 0;
  bool neg = false, zer = false;

  if (fread(&memID, 1, 4, file) != 4) {
    printf("Erro ao ler o cabeçalho do arquivo.\n");
    fclose(file);
    return 1;
  }

  if (memID != 0x52444E03) {
    printf("O arquivo fornecido não corresponde a um formato conhecido do "
           "Neander.\n");
    fclose(file);
    return 1;
  }

  for (int i = 0; i < 512; i++) {
    if (i % 2 == 1) {
      if (fread(&byte, 1, 1, file) != 1) {
        printf("Erro ao ler o arquivo.\n");
        fclose(file);
        return 1;
      }
    } else {
      if (fread(&byte, 1, 1, file) != 1) {
        printf("Erro ao ler o arquivo.\n");
        fclose(file);
        return 1;
      }
      bytes[getByte++] = byte;
    }
  }
  fclose(file);

  while (bytes[pc] != HLT) {
    neg = (ac >= 0x80);
    zer = (ac == 0);

    switch (bytes[pc]) {
    case STA:
      pc++;
      bytes[bytes[pc]] = ac;
      break;
    case LDA:
      pc++;
      ac = bytes[bytes[pc]];
      break;
    case ADD:
      pc++;
      ac += bytes[bytes[pc]];
      break;
    case NOT:
      ac = ~ac;
      break;
    case JMP:
      pc++;               // Primeiro, incrementa pc
      pc = bytes[pc] - 1; // Depois, usa o valor atualizado
      break;
    case JN:
      pc++;
      if (neg)
        pc = bytes[pc] - 1;
      break;
    case JZ:
      pc++;
      if (zer)
        pc = bytes[pc] - 1;
      break;
    }
    pc++;
  }

  printf("\nAC: %02x - PC: %02x\nflags: N(%c) - Z(%c)\n", ac, pc,
         neg ? '*' : ' ', zer ? '*' : ' ');

  printf("\nMemória final =========================================");
  for (int i = 0; i < 256; i++) {
    if (i % 16 == 0)
      printf("\n%07x ", i);
    printf("%02x ", bytes[i]);
  }
  printf("\n=======================================================\n");
  printf("Finalizou com sucesso!\n\n");
  return 0;
}