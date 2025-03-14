# Compiladores SENAC - Atividades

Este repositório contém as atividades do curso de Compiladores do SENAC, que abordam a implementação de um simulador de código Neander (executor) e um analisador léxico (lexer). Cada módulo possui seus próprios passos de compilação e execução.

## Estrutura do Repositório

O repositório contém as seguintes pastas e arquivos:

- `neander/` - Contém o código do simulador Neander.
- `lexer/` - Contém o código do analisador léxico (lexer).

## Módulo Executor (Neander)

Este módulo implementa um simulador de código Neander. Siga os passos abaixo para compilar e executar o código.

### Passos para Compilar e Executar

1. **Entrar na pasta `neander`**:

    ```bash
    cd D:/maquina-virtual-lucashernandez90-main/atividades/neander
    ```

2. **Compilar o código**:

    ```bash
    gcc -o neander neander.c executor.c
    ```

3. **Executar o simulador com um arquivo `.mem`**:

    ```bash
    ./neander program.mem
    ```

## Módulo Executor (Lexer)

1. **Entrar na pasta `lexer`**:

    ```bash
    cd D:/maquina-virtual-lucashernandez90-main/atividades/lexer
    ```

2. **Compilar o código**:

    ```bash
    gcc -o lexer main.c Lexer.c -Wall -Wextra
    ```

3. **Executar o Arquivo txt**:

    ```bash
    ./lexer Entrada.txt
    ```