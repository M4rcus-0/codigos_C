#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

typedef struct player
{
    char nome[4];
    int pontuacao;
    char marcador;
} Player;

typedef struct jogo
{
    Player *player1;
    Player *player2;
} Jogo;

void iniciarJogo(Jogo *jogo, bool resultado);
void resetarJogo(char *tabuleiro);
void imprimirJogo(char *tabuleiro);
bool checarEspacoVazio(char *tabuleiro);
void movimentoPlayer(char *tabuleiro, char valor);
void movimentoComputador(char *tabuleiro, char valor);
void verificarVencedor(char *tabuleiro, Jogo *jogo, char *vencedor);
void imprimirVencedor(char vencedor[]);
bool sortearPlayer();

int main()
{
    setlocale(LC_ALL, "utf-8");
    srand(time(NULL));
    char *tabuleiro = (char *)malloc(3 * 3 * sizeof(char));
    if (tabuleiro == NULL)
    {
        printf("Erro de alocação de mémoria\n");
        return -1;
    }
    char escolha, valor, vencedor[4] = {" "};
    bool sorteio, bot, jogador, continuar = true;
    Jogo jogo;
    jogo.player1 = (Player *)malloc(sizeof(Player));
    jogo.player2 = (Player *)malloc(sizeof(Player));
    strcpy(vencedor, " ");
    printf("Pressione qualquer tecla para iniciar o jogo. . .\n");
    getchar();
    printf("Deseja jogar com o computador? < s | n >\n");
    do
    {
        scanf("%c", &escolha);
        getchar();
        if (escolha != 's' && escolha != 'n')
        {
            printf("Opção inválida\n");
        }
    } while (escolha != 's' && escolha != 'n');
    bot = (escolha == 's') ? true : false;
    iniciarJogo(&jogo, bot);
    sorteio = sortearPlayer();
    do
    {
        resetarJogo(tabuleiro);
        printf("O primeiro(a) a jogar será %s\n", (sorteio == true) ? jogo.player1->nome : jogo.player2->nome);
        do
        {

            printf("Escolha seu marcador < x | o >\n");
            scanf("%c", &valor);
            getchar();
            if (valor != 'x' && valor != 'o')
            {
                printf("Os valores são somente 'x' e 'o'\n");
            }
        } while (valor != 'x' && valor != 'o');
        if (sorteio == true || bot == true)
        {
            jogo.player1->marcador = valor;
            jogo.player2->marcador = (jogo.player1->marcador == 'x') ? 'o' : 'x';
        }
        else if (sorteio == false && bot == false)
        {
            jogo.player2->marcador = valor;
            jogo.player1->marcador = (jogo.player2->marcador == 'x') ? 'o' : 'x';
        }
        jogador = sorteio;
        while (strcmp(vencedor, " ") == 0 && checarEspacoVazio(tabuleiro) == true)
        {
            imprimirJogo(tabuleiro);
            if (jogador == true)
            {
                printf("%s\n", jogo.player1->nome);
                movimentoPlayer(tabuleiro, jogo.player1->marcador);
            }
            else if (jogador == false && bot == false)
            {
                printf("%s\n", jogo.player2->nome);
                movimentoPlayer(tabuleiro, jogo.player2->marcador);
            }
            else if (jogador == false && bot == true)
            {
                printf("%s\n", jogo.player2->nome);
                movimentoComputador(tabuleiro, jogo.player2->marcador);
            }
            verificarVencedor(tabuleiro, &jogo, vencedor);

            if (strcmp(vencedor, jogo.player1->nome) == 0)
            {
                jogo.player1->pontuacao++;
            }
            else if (strcmp(vencedor, jogo.player2->nome) == 0)
            {
                jogo.player2->pontuacao++;
            }
            else if (checarEspacoVazio(tabuleiro) == false)
            {
                printf("Empate!\n");
                break;
            }
            jogador = !jogador;
        }
        imprimirJogo(tabuleiro);
        imprimirVencedor(vencedor);
        printf("Deseja continuar jogando? < s | n >\n");
        do
        {
            scanf("%c", &escolha);
            getchar();
            if (escolha != 's' && escolha != 'n')
            {
                printf("Opção inválida\n");
            }
        } while (escolha != 's' && escolha != 'n');
        continuar = (escolha == 's') ? true : false;
        strcpy(vencedor, " ");
        sorteio = !sorteio;
    } while (continuar == true);

    free(tabuleiro);
    free(jogo.player1);
    free(jogo.player2);
    return 0;
}

void iniciarJogo(Jogo *jogo, bool resultado)
{
    printf("Digite o nome do player1: ");
    fgets(jogo->player1->nome, 4, stdin);
    getchar();
    jogo->player1->nome[strcspn(jogo->player1->nome, "\n")] = '\0';
    strupr(jogo->player1->nome);
    if (resultado != true)
    {
        printf("Digite o nome do player2: ");
        fgets(jogo->player2->nome, 4, stdin);
        getchar();
        jogo->player2->nome[strcspn(jogo->player2->nome, "\n")] = '\0';
        strupr(jogo->player2->nome);
    }
    else
    {
        strcpy(jogo->player2->nome, "COM\0");
    }
    jogo->player1->pontuacao = 0;
    jogo->player2->pontuacao = 0;
}

void resetarJogo(char *tabuleiro)
{
    for (int i = 0; i < 9; i++)
    {
        tabuleiro[i] = ' ';
    }
}

void imprimirJogo(char *tabuleiro)
{
    printf("   1   2   3 \n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d  %c | %c | %c ", i + 1, tabuleiro[(i * 3) + 0], tabuleiro[(i * 3) + 1], tabuleiro[(i * 3) + 2]);
        printf("%s", (i != 2) ? "\n  ---|---|---\n" : "\n\n");
    }
}

bool checarEspacoVazio(char *tabuleiro)
{
    for (int i = 0; i < 9; i++)
    {
        if (tabuleiro[i] == ' ')
        {
            return true;
        }
    }
    return false;
}

void movimentoPlayer(char *tabuleiro, char valor)
{
    int x, y;
    do
    {
        printf("Digite a posição em que você pretende jogar < coluna - linha >: ");
        scanf("%d %d", &x, &y);
        getchar();
        x--;
        y--;
        if (x >= 0 && x < 3 && y >= 0 && y < 3 && tabuleiro[(y * 3) + x] == ' ')
        {
            tabuleiro[(y * 3) + x] = valor;
            break;
        }
        else
        {
            printf("Escolha inválida\n");
        }
    } while (true);
}

void movimentoComputador(char *tabuleiro, char valor)
{
    int pos;
    do
    {
        pos = rand() % 9;
        if (tabuleiro[pos] == ' ')
        {
            tabuleiro[pos] = valor;
            break;
        }
    } while (true);
}

void verificarVencedor(char *tabuleiro, Jogo *jogo, char *vencedor)
{
    for (int i = 0; i < 3; i++)
    {
        if (tabuleiro[i * 3] == tabuleiro[(i * 3) + 1] && tabuleiro[(i * 3) + 1] == tabuleiro[(i * 3) + 2] && tabuleiro[i * 3] != ' ')
        {
            strcpy(vencedor, (tabuleiro[i * 3] == jogo->player1->marcador) ? jogo->player1->nome : jogo->player2->nome);
            return;
        }
        if (tabuleiro[i] == tabuleiro[i + 3] && tabuleiro[i + 3] == tabuleiro[i + 6] && tabuleiro[i] != ' ')
        {
            strcpy(vencedor, (tabuleiro[i] == jogo->player1->marcador) ? jogo->player1->nome : jogo->player2->nome);
            return;
        }
    }
    if (tabuleiro[0] == tabuleiro[4] && tabuleiro[4] == tabuleiro[8] && tabuleiro[0] != ' ')
    {
        strcpy(vencedor, (tabuleiro[0] == jogo->player1->marcador) ? jogo->player1->nome : jogo->player2->nome);
        return;
    }
    if (tabuleiro[2] == tabuleiro[4] && tabuleiro[4] == tabuleiro[6] && tabuleiro[2] != ' ')
    {
        strcpy(vencedor, (tabuleiro[2] == jogo->player1->marcador) ? jogo->player1->nome : jogo->player2->nome);
        return;
    }
    strcpy(vencedor, " ");
    return;
}

void imprimirVencedor(char vencedor[])
{
    if (strcmp(vencedor, " ") != 0)
    {
        printf("O vencedor é %s\n", vencedor);
    }
    else
    {
        printf("Empate!\n");
    }
}

bool sortearPlayer()
{
    return rand() % 2;
}
