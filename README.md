# Jogo da Velha em C

Este é um simples jogo da velha implementado em linguagem C. O jogo permite partidas entre dois jogadores, armazenando resultados e gerando arquivos de histórico para acompanhamento.

## Funcionalidades

- **Jogo para 2 jogadores**
- Alternância automática entre jogadores
- Jogadas marcadas com X e O com cores diferenciadas
- Histórico detalhado das partidas salvo em arquivos `.txt`
- Opções configuráveis através do arquivo `opcoes.txt`
- Modo de debug para facilitar o desenvolvimento e testes

## Funcionalidades do arquivo de opções

No arquivo `opcoes.txt` você pode configurar:
- **Modo de Debug**:
  - 0: Desativado (Padrão)
  - 1: Simples (com avisos e monitoramento)
  - 2: Automatizado (jogadas aleatórias)

- **Limpeza de Tela**:
  - 1: Ativado (padrão)
  - 0: Desativado

- **Modo de Salvamento de Histórico**:
  - 1: Salva histórico utilizando data e hora (recomendado para OnlineGDB)
  - 0: Salva histórico em arquivo único chamado `partida.txt` (recomendado para Replit)

## Compilação e Execução

### Compatibilidade

Este projeto foi desenvolvido e testado nas seguintes IDEs:
- **OnlineGDB**: Totalmente funcional (recomendado).
- **DevC++**: 100% funcional.
- **Replit**: Funciona parcialmente; altere `ModoDeSalvamento` para `0` devido a restrições na função de data e hora.

### Compilação

Compilação básica usando GCC:
```bash
gcc main.c -o jogo_da_velha
```

### Execução

Execute o programa gerado:

```bash
./jogo_da_velha
```

## Funções do arquivo `arq.h`

- `arq_gerar`: Gera arquivos `.txt` com verificação de existência.
- `arq_ler`: Lê conteúdo de arquivos `.txt`.
- `arq_obterData`: Obtém data e hora atual, adaptando-se ao sistema operacional.
- `arq_gerarcData`: Cria arquivos com nomes baseados na data e hora atual.
- `arq_gerarCopia`: Cria cópias de arquivos existentes.
- `arq_criarOpcoes`: Gera o arquivo padrão `opcoes.txt`.
- `arq_lerOpcoes`: Lê valores de configuração do `opcoes.txt`.
- `arq_verificarOpcoes`: Verifica se o `opcoes.txt` existe e o gera, se necessário.

## Como usar

1. Clone ou faça o download do repositório.
2. Compile o arquivo `main.c` em seu compilador favorito.
3. Execute o programa compilado.
4. Siga as instruções no terminal para jogar.

## Autor

Desenvolvido por Arthur Farias.

