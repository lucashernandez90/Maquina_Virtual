# Compiladores SENAC - Atividades

Este repositório contém as atividades do curso de Compiladores do SENAC, que abordam a implementação de um simulador de código Neander (executor) e um analisador léxico (lexer). Cada módulo possui seus próprios passos de compilação e execução.

## Estrutura do Repositório

O repositório contém as seguintes pastas e arquivos:

- `neander/` - Contém o código do simulador Neander.
- `lexer/` - Contém o código do analisador léxico (lexer).
- `compilador/` - Contém o código do compilador que traduz programas `.lpn` para `.asm`.

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

## Módulo Compilador

Este módulo implementa um compilador simples que traduz um programa escrito em linguagem `.lpn` para `.asm`, depois monta para `.bin` e executa o binário na Máquina Neander.

### Componentes

- `main.c`: ponto de entrada do compilador.
- `parser.c/.h`: interpreta comandos do programa `.lpn`.
- `gerador_asm.c/.h`: gera o `.asm` a partir do parse.
- `assembler.c`: transforma `.asm` em `.bin`.
- `executor.c`: executa o binário na VM.

### Fluxo de Compilação

```bash
arquivo.lpn → (parser + gerador_asm) → arquivo.asm → (assembler) → arquivo.bin → (neander) → execução
```
### Rodar manualmente os arquivos

- Primeiro execute `main.c` , `parser.c` , `executor.c` e  `assembler.c` para gerar os executaveis do programa

```bash
gcc main.c parser.c gerador_asm.c -o compilador
gcc assembler.c -o assembler
gcc executor.c neander.c -o executor
```

- Depois de executar esses comandos gere os arquivos `.asm` , `.bin` e depos vai executar o VM

```bash
./compilador exemplo.lpn      
./assembler exemplo.asm       
./executor exemplo.bin        
```

### Exemplo de `.lpn`

```bash
PROGRAMA "teste_simples":
INICIO
A = 5     
B = 3     
C = A * B 
D = C / B 
RES = (A * B + B) / C
FIM
```

### Rodar com o Makefile

- No terminal apenas tem que digitar `make`, para poder rodar o código.

- E se quiser limpar os arquivos que forem gerados digite `make clean`


# Código BNF Explicação

## Estrutura Geral

```bash
<programa> ::= <titulo> <inicio> <comando> "\n" <RES> "\n" <fim>
```
### Esse é o ponto de entrada da gramática

- Título → `PROGRAMA "nome"`:
- Início → `INICIO`
- Comandos → `Declarações e operações matemáticas`
- Resultado (RES) → `RES = valor`
- Fim → `FIM`

### Definição do título

```bash
<titulo> ::= "PROGRAMA \"" <ident> "\":" "\n"
```

- O programa deve começar com a palavra `"PROGRAMA"`
- O nome do programa `<ident>` é um identificador
- No final temos os caracteres `":\n"` para finalizar a linha


### Início e fim do programa

```bash
<inicio> ::= "INICIO\n"
<fim> ::= "FIM"
```

- `INICIO\n` → Indica o começo do programa.
- `FIM` → Indica o fim do programa.


### Definição do resultado (RES)

```bash
<RES> ::= "RES" <espaco> "=" <espaco> <expressao>
```

- `RES` = guarda o resultado final da execução.
- `<expressao>`, pode ser um número ou uma conta matemática.

### Comandos

```bash
<comando> ::= <atribuicao>
            | <comando> "\n" <comando>
```

Comando pode ser:

1. Uma atribuição `(x = 10)`
2. Ou múltiplos comandos separados por quebras de linha.

### Atribuição de variáveis

```bash
<atribuicao> ::= <espaco> <ident> <espaco> "=" <espaco> <expressao>
```

- Formato: variável = expressão
- Permite espaços `<espaco>` antes e depois dos elementos.

### Exemplo

```bash
x = 10
y = x + 5
```

### Expressões matemáticas

```bash
<expressao> ::= <expressao1> ( <espaco> <operador_soma> <espaco> <expressao1> )*
```
Uma expressão pode ser:

1. Apenas um número ou variável.
2. Uma soma/subtração de expressões.

### Exemplo

```bash
x + y
a - 5
```

### Multiplicações e divisões

```bash
<expressao1> ::= <expressao2> ( <espaco> <operador_mult> <espaco> <expressao2> )*
```

- Primeiro, resolve as multiplicações e divisões.
- A precedência é respeitada (multiplicações/divisões antes de somas ou subtrações).

```bash
x * 10 + y / 2
```

A divisão seria feita antes da soma

### Fatores dentro das expressões

```bash
<expressao2> ::= <numero> | <ident> | "(" <espaco> <expressao> <espaco> ")"
```

- Um fator pode ser:

1. Um número (10, 3.14)
2. Um identificador (x, y)
3. Uma expressão entre parênteses.

### Exemplo

```bash
(x + y) * 2
```
###  Operadores matemáticos

```bash
<operador_soma> ::= "+" | "-"
<operador_mult> ::= "*" | "/"
```
- Define adição, subtração, multiplicação e divisão.

### Espaços opcionais

```bash
<espaco> ::= (" " | "\t")*
```

- Permite espaços `(" ")`ou tabulações `("\t")`.
- `*` → Significa zero ou mais espaços permitidos.

### Exemplos

```bash
x=10
x    =    10
```

### Identificadores (variáveis)

```bash
<ident> ::= ([a-z] | [A-Z])+
```

- Um identificador é formado por letras maiúsculas ou minúsculas.
- Não aceita números no começo.

### Números

```bash
<numero> ::= <positivo> | <negativo>
```

- Pode ser um número positivo ou negativo.

### Números positivos

```bash
<positivo> ::= ("0" | [1-9] [0-9]*) ("," [0-9]+)? <cientifico>?
```

- Pode começar com `0` ou um número entre `1-9` seguido de mais dígitos.
- Permite números decimais (`,` seguido de números).
- Pode ter notação científica.

### Exemplos

```bash
0
123
3,14
2e5
```

### Notação científica

```bash
<cientifico> ::= "e" "-"? [1-9] [0-9]*
```

- `e` → Indica notação científica.
- `"-"?` → O expoente pode ser negativo.
- `[1-9] [0-9]*` → O expoente não pode começar com 0.

```bash
2e3    (equivale a 2000)
5,6e-2 (equivale a 0.056)
```