#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#define tamanhoMat 10
#define limite 20

// Usem uma estrutura de dados matricial para armazenar o quadro de letras.
char mat[tamanhoMat][tamanhoMat];

// Usem struct para representar um jogador.
typedef struct
{
    char nome[10];
    int pontuacao;
} jogador;

void matriz();
jogador participantes(int x);
int pesquisaHorizontalLeste(jogador jogador[], int w, char x[], int y, int z);
int pesquisaHorizontalOeste(jogador jogador[], int w, char x[], int y, int z);
int pesquisaVerticalSul(jogador jogador[], int w, char x[], int y, int z);
int pesquisaVerticalNorte(jogador jogador[], int w, char x[], int y, int z);
int pesquisaDiagonalSudeste(jogador jogador[], int w, char x[], int y, int z);
int pesquisaDiagonalSudoeste(jogador jogador[], int w, char x[], int y, int z);
int pesquisaDiagonalNordeste(jogador jogador[], int w, char x[], int y, int z);
int pesquisaDiagonalNoroeste(jogador jogador[], int w, char x[], int y, int z);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    jogador J[limite];
    int semente, total, tamanho, maior = -999999;
    char valor[tamanhoMat], parametro;
    printf("Digite uma 'semente' (int): \n");
    scanf("%d", &semente);
    fflush(stdin);
    // Usem a função srand e rand da biblioteca time.h para gerar a seed e os caracteres.
    srand(semente);
    matriz();
    // O jogo deve ter no mínimo dois jogadores.
    printf("Quantos jogadores?\n");
    do
    {
        scanf("%d", &total);
        fflush(stdin);
        if (total < 2)
        {
            printf("O número de jogadores devem ser no mínimo 2.\n");
        }
    } while (total < 2);
    for (int i = 0; i < total; i++)
    {
        J[i] = participantes(i);
    }

    for (int i = 0; i < total; i++)
    {
        J[i].pontuacao = 0;
    }
    do
    {
        int resultado = 0;
        for (int i = 0; i < total; i++)
        {
            printf("%s, qual a sua palavra:", J[i].nome);
            fgets(valor, tamanhoMat + 1, stdin);
            tamanho = strlen(valor) - 1;
            printf("\n");
            if (i == 0)
            {
                if (strncmp(valor, ".", 1) == 0)
                {
                    parametro = '.';
                    i = total;
                }
                // As palavras digitadas pelos jogadores devem conter no mínimo dois caracteres.
                else if (tamanho > 1)
                {
                    resultado = pesquisaHorizontalLeste(J, resultado, valor, i, tamanho);
                    resultado = pesquisaHorizontalOeste(J, resultado, valor, i, tamanho);
                    resultado = pesquisaVerticalSul(J, resultado, valor, i, tamanho);
                    resultado = pesquisaVerticalNorte(J, resultado, valor, i, tamanho);
                    resultado = pesquisaDiagonalSudeste(J, resultado, valor, i, tamanho);
                    resultado = pesquisaDiagonalSudoeste(J, resultado, valor, i, tamanho);
                    resultado = pesquisaDiagonalNordeste(J, resultado, valor, i, tamanho);
                    resultado = pesquisaDiagonalNoroeste(J, resultado, valor, i, tamanho);
                    if (resultado >= 8)
                    {
                        printf("Palavra não encontrada!\n");
                        J[i].pontuacao--;
                        resultado = 0;
                    }
                }
                else
                {
                    printf("Palavra inválida!\n");
                }
            }
            // As palavras digitadas pelos jogadores devem conter no mínimo dois caracteres.
            else if (tamanho > 1)
            {
                resultado = pesquisaHorizontalLeste(J, resultado, valor, i, tamanho);
                resultado = pesquisaHorizontalOeste(J, resultado, valor, i, tamanho);
                resultado = pesquisaVerticalSul(J, resultado, valor, i, tamanho);
                resultado = pesquisaVerticalNorte(J, resultado, valor, i, tamanho);
                resultado = pesquisaDiagonalSudeste(J, resultado, valor, i, tamanho);
                resultado = pesquisaDiagonalSudoeste(J, resultado, valor, i, tamanho);
                resultado = pesquisaDiagonalNordeste(J, resultado, valor, i, tamanho);
                resultado = pesquisaDiagonalNoroeste(J, resultado, valor, i, tamanho);
                if (resultado >= 8)
                {
                    printf("Palavra não encontrada!\n");
                    J[i].pontuacao--;
                    resultado = 0;
                }
            }
            else
            {
                printf("Palavra inválida!\n");
            }
        }

    } while (parametro != '.');
    for (int i = 0; i < total; i++)
    {
        if (J[i].pontuacao > maior)
        {
            maior = J[i].pontuacao;
        }
    }
    printf("Vencedor(es):");
    for (int i = 0; i < total; i++)
    {
        if (J[i].pontuacao == maior)
        {
            printf("%s ", J[i].nome);
        }
    }
    return 0;
}

void matriz()
{
    int x, y;
    for (x = 0; x < tamanhoMat; x++)
    {
        for (y = 0; y < tamanhoMat; y++)
        {
            mat[x][y] = rand() % (122 - 97 + 1) + 97;
        }
    }
    printf("\nCaça palavras:\n\n");
    for (x = 0; x < tamanhoMat; x++)
    {
        for (y = 0; y < tamanhoMat; y++)
        {
            printf("%c ", mat[x][y]);
        }
        printf("\n");
    }
    printf("\n");
}

// Para ler um jogador, use uma função que retorne uma variável do tipo Jogador.
jogador participantes(int x)
{
    jogador Jogador;
    printf("Nome do jogador %d:\n", x + 1);
    fgets(Jogador.nome, 10, stdin);
    Jogador.pontuacao = 0;
    return Jogador;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaHorizontalLeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int cont = 0;
            while (mat[i][j + cont] == x[cont] && mat[j][j + cont] != '\0' && cont != z && (j + cont) != 10)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Horizontal (Leste --> Oeste) na linha %d coluna %d\n", x, i, j);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaHorizontalOeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = tamanhoMat - 1; j > -1; j--)
        {
            int cont = 0;
            while (mat[i][j - cont] == x[cont] && cont != z && j != 0)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Horizontal (Oeste --> Leste) na linha %d coluna %d\n", x, i, j);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaVerticalSul(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int cont = 0;
            while (mat[j + cont][i] == x[cont] && mat[j + cont][i] != '\0' && cont != z && j != 10)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Vertical (Norte --> Sul) na linha %d coluna %d\n", x, j, i);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaVerticalNorte(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = tamanhoMat - 1; j > -1; j--)
        {
            int cont = 0;
            while (mat[j - cont][i] == x[cont] && cont != z && j != 10)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Vertical (Sul --> Norte) na linha %d coluna %d\n", x, j, i);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaDiagonalSudeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            int cont = 0;
            while (mat[i + cont][j + cont] == x[cont] && mat[i + cont][j + cont] != '\0' && cont != z && j != 10)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Diagonal (Noroeste --> Sudeste) na linha %d coluna %d\n", x, i, j);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaDiagonalSudoeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = tamanhoMat - 1; j > -1; j--)
        {
            int cont = 0;
            while (mat[i + cont][j - cont] == x[cont] && mat[j - cont][i + cont] != '\0' && cont != z && j != 0)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Diagonal (Nordeste --> Sudoeste) na linha %d coluna %d\n", x, i, j);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaDiagonalNordeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = tamanhoMat - 1; j > -1; j--)
        {
            int cont = 0;
            while (mat[j - cont][i + cont] == x[cont] && mat[j - cont][i + cont] != '\0' && cont != z && j != 10)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Diagonal (Sudoeste --> Nordeste) na linha %d coluna %d\n", x, j, i);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}

// Usem funções para verificar se a palavra existe no puzzle (uma função pra cada sentido).
int pesquisaDiagonalNoroeste(jogador Jogador[], int w, char x[], int y, int z)
{
    int naoencontrado = 0;
    for (int i = tamanhoMat - 1; i > -1; i--)
    {
        for (int j = tamanhoMat - 1; j > -1; j--)
        {
            int cont = 0;
            while (mat[i - cont][j - cont] == x[cont] && mat[j - cont][i - cont] != '\0' && cont != z && j != 0)
            {
                cont++;
                if (cont == (z))
                {
                    printf("Palavra %s encontrada na Diagonal (Sudeste --> Noroeste) na linha %d coluna %d\n", x, i, j);
                    naoencontrado++;
                    Jogador[y].pontuacao++;
                    w = 0;
                }
            }
        }
    }
    if (naoencontrado == 0)
    {
        w++;
    }
    return w;
}
