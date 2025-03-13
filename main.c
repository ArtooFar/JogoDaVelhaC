// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - //
// IDES TESTADOS:
// Onlinegdb (onde foi feito) - funciona 100%
// Replit - funciona, mas o salvamento de arquivo não funciona 100% -> trocar o Modo de Salvamento para 0
// DevC++ - funciona 100%
// - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - // - //

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <ctype.h>
//Esses próximos 2 são pra função aleatorio()
#include <stdlib.h>
#include <time.h>
// P usa a função que troca a localização do texto (pelo q entendi) -> setlocale
// N precisa nos ide online mas pra mostrar certo compilado pelo Dev C++ precisa
#include <locale.h>

// Se tiver tentando compilar no Windows ele inclui essa blblioteca:
#ifdef _WIN32
#include <windows.h>
#endif

//Bibliotecas próprias
#include "arq.h"

//Funções

//-Matriz-//
void construirMatriz (char espaco[][3][3],int part,int cor[][3][3]);
void limparMatriz (char espaco[][3][3],int part,int cor[][3][3]);
int verificarVitoria (char espaco[][3][3],int part, int cor[][3][3]);

//-Interação c/o Jogador-//
void jogar (int player, char *jogador,int jogada,char espaco[][3][3],int part,int vitJ1,int vitJ2,int debug,int cor[][3][3]);
void pressEnter (int debug,int debugclear);
void inserirJogador (int num, char *jogador,int debug);
void fim (char espaco[][3][3],int part,char *jog1,char *jog2,int debugclear,int cor[][3][3]);

//-Texto-//
void titulo ();
void posInicio (char jog1[],char jog2[]);
void tutorial (int debug,int debugclear);

//-Funções Independentes-//
int aleatorio (int min, int max);
void limparTela();

//-Funçoes da arq.h-//
//->Gerenciamento de Arquivos
void arq_gerar (char principal[], char arqmontado[],int modo, int debug);
void arq_ler (int limite, char arq_nome[],int debug);
void arq_obterData (char arq_nome[]);
void arq_gerarcData (char arq_nome[],int debug, int debugclear);
void arq_gerarCopia (char arq_nome[], char arq_nomeCopia[], int debug);
void arq_criarOpcoes ();
int arq_lerOpcoes (int *variavel, char scan[], char formato[]);
int arq_verificarOpcoes ();
//->String
int str_iniciaCom (char stringA[],char stringB[]);

//-Gerenciamento de Arquivos-//
void arq_construirMatriz (char espaco[][3][3], int part, int cor[][3][3], char arq_nome[], char jog1[], char jog2[], int debug);
void arq_gerarHistorico (char espaco[][3][3], int part, int cor[][3][3], char arq_nome[], char jog1[], char jog2[], int vencedorFinal, int debug);




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//INÍCIO DA MAIN -- INÍCIO DA MAIN -- INÍCIO DA MAIN -- INÍCIO DA MAIN -- INÍCIO DA MAIN -- INÍCIO DA MAIN //
////////////////////////////////////////////////////////////////////////////////////////////////////////////




int main()
{
    //Configuração de Console pro Windows ---------------------
    
    setlocale(LC_ALL, "Portuguese_Brazil.UTF-8");
    // Faz compilar só no windows
    #ifdef _WIN32
    
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        if (GetConsoleMode(hOut, &dwMode)) {
            dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, dwMode);
        }
        SetConsoleOutputCP(65001);

    #endif
    
    //Configuração de Console pro Windows ^^^^^^^^^^^^^^^^^^^^

    //////////////////////////// INICIALIZAÇÃO - ARQUIVOS - CONFIGURAÇÕES ////////////////////////////////
    
    //Variáveis das configurações -> opcoes.txt
    int debug, debugclear, modoDeSalvamento;
    //Verifica se o opcoes.txt já foi criado
    if (arq_verificarOpcoes() ==1) return 10;
    //Obter variáveis guardadas em opcoes.txt
    arq_lerOpcoes(&debug,"debug = ","debug = %d");
    arq_lerOpcoes(&debugclear,"LimparTela = ","LimparTela = %d");
    arq_lerOpcoes(&modoDeSalvamento,"ModoDeSalvamento = ","ModoDeSalvamento = %d");
    
    //////////////////////////// INICIALIZAÇÃO - ARQUIVOS - CONFIGURAÇÕES ////////////////////////////////
    
    //Definir Seed como Tempo
    srand(time(0));
    int player= aleatorio(1,2),jogada,vit=0,cor[3][3][3],vencedorFinal;
    char arq_nome[60],jog1[30],jog2[30], espaco[3][3][3],vitJ1=0,vitJ2=0,part=0;
    limparMatriz(espaco,part,cor);
    
    if (modoDeSalvamento==1) arq_gerarcData(arq_nome,debug,debugclear);
    else arq_gerar("partida", arq_nome, 2, debug);

    //Início - titulo, inserção de nomes e tutorial
    if (debug>0) printf("Player a começar : %d\n",player); // Debug
    
    titulo();
    
    inserirJogador(1,jog1,debug);
    inserirJogador(2,jog2,debug);
    
    posInicio(jog1,jog2);
    construirMatriz(espaco,part,cor);
    tutorial(debug,debugclear);
    
    //Loop de Jogo
    
    while(part<3){
        printf("============================================================\n");
        construirMatriz(espaco,part,cor);
        for (int i=0;i<9;i++) {
            jogada=i+1;
            
            //Selecionar posição da jogada
            if (player==1) jogar(player, jog1,jogada,espaco,part,vitJ1,vitJ2,debug,cor);
            if (player==2) jogar(player, jog2,jogada,espaco,part,vitJ1,vitJ2,debug,cor);
            
            //Alternar Player pra prox partida
            player=(player==1) ? 2 : 1;
            
            //Construção de Matriz
            if (debugclear==1) limparTela();
            
            printf("============================================================\n");
            construirMatriz(espaco,part,cor);
            
            //Verificação de vitória da rodada
            vit=verificarVitoria(espaco,part,cor);
            
            if (vit==1) {
                printf(" Parabéns! \x1b[91m%s\x1b[39m, você ganhou essa rodada!\n",jog1);
                pressEnter(debug,debugclear);
                vitJ1++;
                break;
            } 
            else if (vit==2) {
                printf(" Parabéns! \x1b[94m%s\x1b[39m, você ganhou essa rodada!\n",jog2);
                pressEnter(debug,debugclear);
                vitJ2++;
                break;
            }
            if (i==8 && vit==0) {
                printf(" Deu velha!\n");
                pressEnter(debug,debugclear);
            }
            ///////////////////////////
        
        //Indicar vencedor ou empate
        }
        if (vitJ1==2 || (vitJ1==1 && part==2 && vitJ2==0)) {
            printf("============================================================\n");
            printf(" Parabéns! \x1b[91m%s\x1b[39m, você ganhou o \x1b[92mJogo da Velha!\x1b[39m\n",jog1);
            vencedorFinal=1;
            break;
        }
        else if (vitJ2==2 || (vitJ2==1 && part==2 && vitJ1==0)) {
            printf("============================================================\n");
            printf(" Parabéns! \x1b[94m%s\x1b[39m, você ganhou o \x1b[92mJogo da Velha!\x1b[39m\n",jog2);;
            vencedorFinal=2;
            break;
        }
        else {
            if (part==2) {
            printf("============================================================\n");
            printf(" O jogo acabou em empate!\n");;
            vencedorFinal=0;
            break;
            }
            else { 
                part++;
                limparMatriz(espaco,part,cor);
            }
        }
    }
    
    
    //Após todos os jogos:
    arq_gerarHistorico(espaco, part, cor, arq_nome, jog1, jog2,vencedorFinal, debug);
    fim(espaco,part,jog1,jog2,debugclear,cor);
    
    return 0;
}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//FIM DA MAIN -- FIM DA MAIN -- FIM DA MAIN -- FIM DA MAIN -- FIM DA MAIN -- FIM DA MAIN -- FIM DA MAIN -- //
////////////////////////////////////////////////////////////////////////////////////////////////////////////




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Matriz - Matriz - Matriz  - Matriz  - Matriz  - Matriz  - Matriz  - Matriz  - Matriz  - Matriz  - Matriz//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void construirMatriz(char espaco[][3][3],int part,int cor[][3][3]){
    printf("\n                          \x1b[1;90m0   1   2\x1b[39m \n");
    printf("                        -------------\n");
    printf("                      \x1b[90m0\x1b[39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m |\n",cor[0][0][part],espaco[0][0][part],cor[0][1][part],espaco[0][1][part],cor[0][2][part],espaco[0][2][part]);
    printf("                        -------------\n");
    printf("                      \x1b[90m1\x1b[39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m |\n",cor[1][0][part],espaco[1][0][part],cor[1][1][part],espaco[1][1][part],cor[1][2][part],espaco[1][2][part]);
    printf("                        -------------\n");
    printf("                      \x1b[90m2\x1b[39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m | \x1b[22;%dm%c\x1b[1;39m |\n",cor[2][0][part],espaco[2][0][part],cor[2][1][part],espaco[2][1][part],cor[2][2][part],espaco[2][2][part]);
    printf("                        -------------\n\n\x1b[22m");
    printf("============================================================\n");
}

void limparMatriz(char espaco[][3][3],int part,int cor[][3][3]){
    
    int cont=0;
    
    for (int i=0;i<3;i++){
        for (int j=0;j<3;j++){
            espaco[i][j][part]=' ';
            cor[i][j][part]=39;
        }
    }
    
}

int verificarVitoria (char espaco[][3][3], int part, int cor[][3][3]) {
    // linhas verticais
    if (espaco[0][0][part] == 'X' && espaco[1][0][part] == 'X' && espaco[2][0][part] == 'X') {
        cor[0][0][part] = 93; cor[1][0][part] = 93; cor[2][0][part] = 93; 
        return 1;
    }
    if (espaco[0][0][part] == 'O' && espaco[1][0][part] == 'O' && espaco[2][0][part] == 'O') {
        cor[0][0][part] = 96; cor[1][0][part] = 96; cor[2][0][part] = 96; 
        return 2;
    }
    
    if (espaco[0][1][part] == 'X' && espaco[1][1][part] == 'X' && espaco[2][1][part] == 'X') {
        cor[0][1][part] = 93; cor[1][1][part] = 93; cor[2][1][part] = 93; 
        return 1;
    }
    if (espaco[0][1][part] == 'O' && espaco[1][1][part] == 'O' && espaco[2][1][part] == 'O') {
        cor[0][1][part] = 96; cor[1][1][part] = 96; cor[2][1][part] = 96;
        return 2;
    }
    
    if (espaco[0][2][part] == 'X' && espaco[1][2][part] == 'X' && espaco[2][2][part] == 'X') {
        cor[0][2][part] = 93; cor[1][2][part] = 93; cor[2][2][part] = 93; 
        return 1;
    }
    if (espaco[0][2][part] == 'O' && espaco[1][2][part] == 'O' && espaco[2][2][part] == 'O') {
        cor[0][2][part] = 96; cor[1][2][part] = 96; cor[2][2][part] = 96;
        return 2;
    }
    
    // linhas horizontais
    if (espaco[0][0][part] == 'X' && espaco[0][1][part] == 'X' && espaco[0][2][part] == 'X') {
        cor[0][0][part] = 93; cor[0][1][part] = 93; cor[0][2][part] = 93; 
        return 1;
    }
    if (espaco[0][0][part] == 'O' && espaco[0][1][part] == 'O' && espaco[0][2][part] == 'O') {
        cor[0][0][part] = 96; cor[0][1][part] = 96; cor[0][2][part] = 96;
        return 2;
    }
    
    if (espaco[1][0][part] == 'X' && espaco[1][1][part] == 'X' && espaco[1][2][part] == 'X') {
        cor[1][0][part] = 93; cor[1][1][part] = 93; cor[1][2][part] = 93; 
        return 1;
    }
    if (espaco[1][0][part] == 'O' && espaco[1][1][part] == 'O' && espaco[1][2][part] == 'O') {
        cor[1][0][part] = 96; cor[1][1][part] = 96; cor[1][2][part] = 96;
        return 2;
    }
    
    if (espaco[2][0][part] == 'X' && espaco[2][1][part] == 'X' && espaco[2][2][part] == 'X') {
        cor[2][0][part] = 93; cor[2][1][part] = 93; cor[2][2][part] = 93; 
        return 1;
    }
    if (espaco[2][0][part] == 'O' && espaco[2][1][part] == 'O' && espaco[2][2][part] == 'O') {
        cor[2][0][part] = 96; cor[2][1][part] = 96; cor[2][2][part] = 96;
        return 2;
    }
    
    // linhas diagonais
    if (espaco[0][0][part] == 'X' && espaco[1][1][part] == 'X' && espaco[2][2][part] == 'X') {
        cor[0][0][part] = 93; cor[1][1][part] = 93; cor[2][2][part] = 93; 
        return 1;
    }
    if (espaco[0][0][part] == 'O' && espaco[1][1][part] == 'O' && espaco[2][2][part] == 'O') {
        cor[0][0][part] = 96; cor[1][1][part] = 96; cor[2][2][part] = 96;
        return 2;
    }
    
    if (espaco[0][2][part] == 'X' && espaco[1][1][part] == 'X' && espaco[2][0][part] == 'X') {
        cor[0][2][part] = 93; cor[1][1][part] = 93; cor[2][0][part] = 93; 
        return 1;
    }
    if (espaco[0][2][part] == 'O' && espaco[1][1][part] == 'O' && espaco[2][0][part] == 'O') {
        cor[0][2][part] = 96; cor[1][1][part] = 96; cor[2][0][part] = 96;
        return 2;
    }
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Interação c/o Jogador - Interação c/o Jogador - Interação c/o Jogador - Interação c/o Jogador - Interaçã//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void jogar(int player, char *jogador,int jogada,char espaco[][3][3],int part,int vitJ1,int vitJ2,int debug,int cor[][3][3]) {
    
    int linha,coluna,contin=1,conterro=0;
    
    printf("                  -=- Jogada %d / Jogo %d -=-\n",jogada,part+1);
    printf("                    -={ J1: %d / J2: %d }=-\n\n",vitJ1,vitJ2);
    if (player==1) printf("\x1b[91mJ%d\x1b[39m: \x1b[91m%s\x1b[39m, Onde colocará sua peça? \x1b[90m[Formato: L,C]\x1b[39m \n",player,jogador);
    if (player==2) printf("\x1b[94mJ%d\x1b[39m: \x1b[94m%s\x1b[39m, Onde colocará sua peça? \x1b[90m[Formato: L,C]\x1b[39m \n",player,jogador);
    
    do {
        if (debug<2) scanf("%d,%d",&linha,&coluna);
        else {
            linha=aleatorio(0,2);
            coluna=aleatorio(0,2);
        }
        
        if (linha>2||coluna>2) printf(" \x1b[91mEssa posição não existe ou houve erro de sintaxe\x1b[39m\n");
        else {
            
            if (espaco[linha][coluna][part] == 'X'|| espaco[linha][coluna][part] == 'O') {
                if (debug<2) printf(" \x1b[93mEssa posição já foi ocupada\x1b[39m\n");
                else {
                    if (conterro==0){
                        conterro++;
                        printf("\x1b[93m Tentativas em posições ocupadas: %d\x1b[39m\n",conterro);
                    }
                    else {
                        conterro++;
                        printf("\x1b[1F\x1b[34C\x1b[0k%d\n",conterro);
                    }
                }
            }
        
            else {
                
                if (player==1) {
                    espaco[linha][coluna][part] = 'X';
                    cor[linha][coluna][part] = 91;
                    contin=0;
                }
                
                if (player==2) {
                    espaco[linha][coluna][part] = 'O';
                    cor[linha][coluna][part] = 94;
                    contin=0;
                }
            }
        }
    } 
    while (contin==1);
}

void pressEnter(int debug,int debugclear) {
    char lixo;
    if (debug<2) getchar();
    //pegar lixo do outro scanf^
    
    printf("============================================================\n");
    printf(" \x1b[1mPressione \x1b[92menter\x1b[39m para continuar...\x1b[22m");
    printf("\n============================================================\n");
    if (debug<2) {
        lixo=getchar();
        if (lixo!='\n') getchar();
    }
    if (debugclear==1) limparTela();
    
}

void inserirJogador(int num, char *jogador,int debug) {
    //Inserção do nome de player
    if (num==1) printf("\x1b[1F\x1b[17C\x1b[94m");
    if (num==2) printf("\x1b[17C\x1b[91m");
    
    if (debug<2) scanf("%s", jogador);
    else {
        if (num==1) strcpy(jogador,"M1au");
        else if (num==2) strcpy(jogador,"H2O");
    }
    
    printf("\x1b[39m");
}

void fim(char espaco[][3][3],int part,char *jog1,char *jog2,int debugclear,int cor[][3][3]) {
    char scan='m';
    int nscan=10,venc;
    
    while(scan!='\n') {
        printf("============================================================\n");
        printf(" \x1b[1;92mInsira um número de partida para visualizá-la\x1b[22;39m\n\n");
        printf(" Ou aperte \x1b[2;91menter\x1b[22;39m para encerrá-lo\n");
        printf(" Total de Rodadas: %d\n",part+1);
        printf("\n============================================================\n");
        scan= getchar();
        
        if (scan=='\n') {
            printf("Obrigado por Jogar!\n");
            break;
        }
        
        if (scan=='1') nscan=1;
        else if (scan=='2') nscan=2;
        else if (scan=='3') nscan=3;
        else if (isdigit(scan)) printf(" Rodada Inválida\n");
        getchar();
        
        if (nscan<=part+1) {
        if (debugclear==1) limparTela();
            printf("============================================================\n");
            printf("\nHistórico // Rodada %d\n",nscan);
            venc=verificarVitoria(espaco,nscan-1,cor);
            if (venc==1) printf("Vencedor(a) -> \x1b[91mJ1 (X): %s\n\x1b[39m",jog1);
            if (venc==2) printf("Vencedor(a) -> \x1b[94mJ2 (O): %s\n\x1b[39m",jog2);
            if (venc==0) printf("Deu Velha!\n");
            construirMatriz(espaco,(nscan-1),cor);
        }
        nscan=10;
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - Texto - //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void titulo(){
    printf("============================================================\n");
    printf("                    -= JOGO DA VELHA =-");
    printf("\n============================================================\n");
    printf("                      Insira os nomes:\n\n");
    printf(" Jogador[\x1b[94m1\x1b[39m] (\x1b[94mX\x1b[39m): \n");
    printf(" Jogador[\x1b[91m2\x1b[39m] (\x1b[91mO\x1b[39m): ");
}

void posInicio(char jog1[],char jog2[]){
    printf("\n  Bem vindos, \x1b[94m%s\x1b[39m e \x1b[91m%s\x1b[39m!\n",jog1,jog2);
    printf("============================================================\n");
}

void tutorial(int debug,int debugclear) {
    printf("                       \x1b[1m--\x1b[92m Tutorial \x1b[39m--\x1b[22m\n\n");
    printf(" Para selecionar a sua jogada, envie dessa forma: \x1b[1;34m'l,c'\n\x1b[41C(l=linha, c=coluna)\x1b[39m\x1b[22m\n\n");
    printf(" A \x1b[91mprimeira pessoa\x1b[39m a jogar será escolhida \x1b[91maleatoriamente!\x1b[39m\n");
    printf(" \n Quem obtiver \x1b[92mmais vitórias\x1b[39m em \x1b[92m3 partidas\x1b[39m vence!\n");
    printf(" \n Para ganhar 1 ponto, complete uma linha nas posições:\n");
    printf("  Horizontal --, Vertical | ou Diagonal / ou \\ \n");
    pressEnter(debug,debugclear);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Funções Independentes - Funções Independentes - Funções Independentes - Funções Independentes - Funções //
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int aleatorio(int min, int max) {
    //Obter numero aleatorio e retornar
    int aleat = (rand() % ((max+1) - min)) + min;
    return aleat;
}

void limparTela() {
//Funciona tipo um system("clear") mas com ANSII Escape Code
    printf("\x1b[H\x1b[0J\x1b[H");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Gerenciamento de Arquivos - Gerenciamento de Arquivos - Gerenciamento de Arquivos - Gerenciamento de Arq//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void arq_construirMatriz(char espaco[][3][3], int part, int cor[][3][3], char arq_nome[], char jog1[], char jog2[],int debug) {
    FILE *arq=fopen(arq_nome,"a");
    
    if (arq) {
        fprintf(arq, "============================================================\n");
        fprintf(arq,"\nHistórico // Rodada %d\n",part+1);
        int venc=verificarVitoria(espaco,part,cor);
        if (venc==1) fprintf(arq,"Vencedor(a) -> J1 (X): %s\n",jog1);
        if (venc==2) fprintf(arq,"Vencedor(a) -> J2 (O): %s\n",jog2);
        if (venc==0) fprintf(arq,"Deu Velha!\n");
            
        fprintf(arq, "\n                          0   1   2\n");
        fprintf(arq, "                        -------------\n");
        fprintf(arq, "                      0 | %c | %c | %c |\n",
                espaco[0][0][part], espaco[0][1][part], espaco[0][2][part]);
        fprintf(arq, "                        -------------\n");
        fprintf(arq, "                      1 | %c | %c | %c |\n",
                espaco[1][0][part], espaco[1][1][part], espaco[1][2][part]);
        fprintf(arq, "                        -------------\n");
        fprintf(arq, "                      2 | %c | %c | %c |\n",
                espaco[2][0][part], espaco[2][1][part], espaco[2][2][part]);
        fprintf(arq, "                        -------------\n\n");
        fprintf(arq, "============================================================\n");
        fclose(arq);
    } else if (debug) printf("Erro na abertura do arquivo -> arq_construirMatriz");
}

void arq_gerarHistorico (char espaco[][3][3], int part, int cor[][3][3], char arq_nome[], char jog1[], char jog2[], int vencedorFinal, int debug){
    
    FILE *arq;
    arq=fopen(arq_nome,"a");
    if (arq) {
        fprintf(arq, "============================================================\n");
        if (vencedorFinal==1) fprintf(arq, "Vencedor Final: J1 | Nome: %s\n",jog1);
        if (vencedorFinal==2) fprintf(arq, "Vencedor Final: J2 | Nome: %s\n",jog2);
        if (vencedorFinal==0) fprintf(arq, "O jogo acabou em empate\n");
        fprintf(arq, "============================================================\n");
        fclose(arq);
        for(int i=0;i<=part;i++) arq_construirMatriz(espaco, i, cor, arq_nome, jog1, jog2, debug);
        
        arq_gerarCopia(arq_nome,"ultimaPartida.txt",debug);
        
    } else if (debug) printf("Erro na abertura de arquivo -> arq_gerarHistorico"); 
}

