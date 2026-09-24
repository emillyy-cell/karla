# Sensor de Temperatura em C — Sistema de Monitoramento

## 1. Identificação

- **Nome do aluno:** Emilly Lorrany Alves dos Santos
- **Disciplina:** Algoritmos e Pensamento Computacional
- **Professora:** Profa. Karla Sartin
- **Título do projeto:** Sistema de Monitoramento de Temperatura em C

## 2. Objetivo

O programa simula um sensor que realiza leituras sucessivas de temperatura e as compara
com um limite definido pelo usuário. O objetivo é identificar automaticamente sequências
de temperaturas consecutivas acima desse limite e encerrar o monitoramento assim que três
leituras consecutivas ultrapassarem o limite, apresentando em seguida um relatório com as
estatísticas do período monitorado (quantidade de leituras, média, maior, menor,
quantidade acima do limite e percentual acima do limite).

## 3. Funcionamento do programa

- **Definição do limite:** o limite de temperatura é digitado pelo usuário no início da
  execução e validado antes de o monitoramento começar.
- **Leituras:** a cada iteração do laço principal, o programa solicita uma nova
  temperatura ao usuário (simulando a leitura de um sensor).
- **Entradas inválidas:** toda entrada (limite ou temperatura) é lida com `scanf("%f", ...)`.
  Se o valor digitado não for numérico, `scanf` retorna `0`, o programa exibe uma mensagem
  de erro, limpa o restante do buffer de entrada (função `limparBufferEntrada`) e solicita
  o valor novamente, sem avançar a lógica do monitoramento.
- **Identificação de temperatura acima do limite:** a cada leitura válida, o valor lido é
  comparado com o limite (`temperatura > limite`).
- **Contador de consecutividade:** existe uma variável `consecutivasAcima` que é
  incrementada sempre que a leitura está acima do limite e **reiniciada para zero** sempre
  que uma leitura está no limite ou abaixo dele. Isso garante que apenas sequências
  realmente consecutivas provoquem o encerramento.
- **Encerramento:** o monitoramento é encerrado automaticamente quando
  `consecutivasAcima` atinge `3` (constante `MAX_CONSECUTIVAS`). Essa é a única condição
  de encerramento do monitoramento, conforme especificado no desafio.
- **Cálculo dos resultados finais:** durante o monitoramento o programa acumula a soma das
  temperaturas, a maior, a menor e a quantidade de leituras acima do limite. Ao final,
  calcula a média (`soma / totalLeituras`) e o percentual acima do limite
  (`(qtdAcimaLimite / totalLeituras) * 100`), usando aritmética em ponto flutuante para
  evitar divisão inteira.

### Suposição técnica assumida

O enunciado define apenas uma condição de encerramento do monitoramento: três
temperaturas consecutivas acima do limite. Não há, no enunciado, previsão de um comando
de saída manual (por exemplo, digitar um valor sentinela). Por isso, o programa **não**
implementa uma forma alternativa de encerrar o monitoramento — o laço principal só termina
quando a condição das três leituras consecutivas é satisfeita. Essa escolha foi feita para
não introduzir um requisito que não está no enunciado. Como consequência, ao testar o
programa, o usuário deve sempre finalizar a sequência de entradas com três leituras
consecutivas acima do limite para que o relatório final seja exibido.

## 4. Estruturas de repetição utilizadas

- **`do...while`** é usado em três pontos:
  1. Validação do limite de temperatura (`main`), pois o valor precisa ser solicitado pelo
     menos uma vez e a solicitação deve se repetir enquanto a entrada não for numérica.
  2. Validação de cada leitura de temperatura, pelo mesmo motivo.
  3. Dentro de `limparBufferEntrada`, o laço `while` percorre os caracteres restantes do
     buffer até encontrar `'\n'` ou `EOF` — ele só executa quando há caracteres a
     descartar, então é um `while` puro (pode não executar nenhuma vez, ao contrário do
     `do...while`, que roda o corpo pelo menos uma vez).
- **`while`** controla o laço principal de monitoramento (`while (consecutivasAcima <
  MAX_CONSECUTIVAS)`), pois a quantidade de leituras necessárias não é conhecida
  previamente — depende de quando ocorrerem três leituras consecutivas acima do limite.

Nenhuma estrutura `for` é utilizada para controlar o monitoramento ou a validação de
entradas, conforme exigido.

## 5. Como executar

O programa foi escrito em C padrão (ANSI C / C89 compatível) e pode ser compilado com o
GCC.

**Linux / macOS:**
```bash
gcc monitoramento.c -o monitoramento
./monitoramento
```

**Windows (terminal do VS Code, com o MinGW/GCC instalado):**
```bash
gcc monitoramento.c -o monitoramento.exe
./monitoramento.exe
```

Após a execução, o programa solicita o limite de temperatura e, em seguida, as leituras
sucessivas, uma a uma.

## 6. Testes realizados

### Teste 1 — Validação de entradas inválidas

**Objetivo:** verificar se o programa trata corretamente uma entrada não numérica, tanto
no limite quanto nas leituras de temperatura.

**Procedimento:** ao ser solicitado o valor, foi digitado um caractere não numérico
(por exemplo, a letra `a`).

**Resultado obtido:** o programa exibiu a mensagem `"Entrada invalida! Digite um valor
numerico..."`, limpou o buffer de entrada e solicitou o valor novamente, sem avançar a
lógica do monitoramento nem contabilizar a tentativa inválida como uma leitura.

📷 Evidência: `evidencias/teste01.png`

### Teste 2 — Temperaturas acima do limite, porém não consecutivas

**Objetivo:** verificar se o contador de leituras consecutivas é reiniciado corretamente
quando a sequência é interrompida.

**Procedimento:** com um limite definido (por exemplo, 30°C), foram informadas
temperaturas alternando entre valores acima e abaixo do limite (ex.: 32, 28, 35, 25, 33).

**Resultado obtido:** a cada vez que uma temperatura ficou dentro do limite, o contador
`consecutivasAcima` voltou a zero e o monitoramento continuou normalmente, sem encerrar,
mesmo havendo várias leituras acima do limite ao longo do teste.

📷 Evidência: `evidencias/teste02.png`

### Teste 3 — Três temperaturas consecutivas acima do limite

**Objetivo:** verificar o encerramento automático do monitoramento.

**Procedimento:** com o mesmo limite definido, foram informadas três temperaturas
seguidas, todas acima do limite (ex.: 32, 34, 36).

**Resultado obtido:** após a terceira leitura consecutiva acima do limite, o laço de
monitoramento foi encerrado automaticamente e o programa exibiu o relatório final,
contendo o total de leituras, a média, a maior e a menor temperatura, a quantidade de
leituras acima do limite, o percentual acima do limite e o motivo do encerramento.

📷 Evidência: `evidencias/teste03.png`

## Questão final de reflexão

Optei por combinar as duas estruturas, `while` e `do...while`, porque cada uma resolve um
problema diferente dentro do mesmo programa. O `do...while` foi usado nos pontos em que a
ação (pedir um valor ao usuário) **precisa acontecer pelo menos uma vez antes de qualquer
verificação**: não faz sentido testar se a entrada é válida antes de ela existir, então o
laço primeiro executa a leitura e só depois avalia a condição de repetição. Essa diferença
foi essencial na validação do limite e das temperaturas: se eu tivesse usado um `while`
comum ali, precisaria de uma leitura "fantasma" antes do laço só para inicializar a
variável testada na condição, o que deixaria o código mais confuso e redundante.

Já o `while` foi usado no laço principal de monitoramento, onde a condição (três leituras
consecutivas acima do limite) só pode ser avaliada **depois de já existir pelo menos uma
leitura**, mas o número total de repetições não é conhecido previamente — pode ser 3
leituras ou 300. Testar a condição antes de cada nova iteração é o que permite ao programa
parar exatamente no momento certo, assim que a condição de encerramento é satisfeita, sem
executar uma iteração a mais desnecessária.

Ou seja, a diferença entre testar a condição antes (`while`) ou depois (`do...while`) da
execução do bloco foi importante justamente para casar cada estrutura com a natureza do
problema que ela resolve: uma entrada que sempre precisa ocorrer pelo menos uma vez
(`do...while`) e um monitoramento que pode ou não continuar, dependendo de um estado que só
existe depois da primeira leitura (`while`).

## Estrutura do repositório

```text
desafio-monitoramento/
│
├── monitoramento.c
├── README.md
└── evidencias/
    ├── teste01.png
    ├── teste02.png
    └── teste03.png
```
