# Jogo da Velha em C

Este é um simples jogo da velha implementado em linguagem C. O jogo permite partidas entre dois jogadores, armazenando resultados e gerando arquivos de histórico para acompanhamento.

## Funcionalidades ✨

- 👥 **Jogo para 2 jogadores**
  
![Jogada](https://github.com/user-attachments/assets/822c1e75-e304-4d02-9028-f5c3a10b3d5f)

- 🔄 **Alternância automática entre jogadores**
- 🎲 **O primeiro jogador é escolhido de forma aleatória**
- ❌⭕ **Jogadas marcadas com X e O com cores diferenciadas**

![Image](https://github.com/user-attachments/assets/bbf12ab4-e553-4814-aba6-b9fa7612d503)

- 📝 **Histórico detalhado das partidas salvo em arquivos**

![Image](https://github.com/user-attachments/assets/14e5eedb-23ca-4b29-98a8-880c4993cafd)
  
- ⚙️ **Opções configuráveis através do arquivo ** `opcoes.txt`
- 🐛 **Modo de debug para facilitar o desenvolvimento e testes**

## Funcionalidades do arquivo de opções 🛠️

No arquivo `opcoes.txt` você pode configurar:

- 🐞 **Modo de Debug**:

  - 0: Desativado (Padrão)
  - 1: Simples (com avisos e monitoramento)
  - 2: Automatizado (jogadas aleatórias)

- 🧹 **Limpeza de Tela**:

  - 1: Ativado (padrão)
  - 0: Desativado

- 💾 **Modo de Salvamento de Histórico**:

  - 1: Salva histórico utilizando data e hora (recomendado para OnlineGDB)
  - 0: Salva histórico em arquivo único chamado `partida.txt` (recomendado para Replit)

## Compilação e Execução 🚀

### Compatibilidade 🖥️

Este projeto foi desenvolvido e testado nas seguintes IDEs:

- 🌐 **OnlineGDB**: Totalmente funcional (recomendado).
- 🖥️ **DevC++**: 100% funcional.
- ☁️ **Replit**: Funciona parcialmente; altere `ModoDeSalvamento` para `0` devido a restrições na função de data e hora.

Você pode jogar diretamente no OnlineGDB, sem necessidade de baixar ou compilar:

▶️ [Jogar no OnlineGDB](https://onlinegdb.com/8Uf-VIijQT)

## Autor 👨‍💻

Desenvolvido por Arthur Farias.

