#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct no
{
    char valor;
    struct no *prox;

} No;

typedef struct pilha
{
    No *topo;
} Pilha;

void inicializar(Pilha *pilha);
void empilhar(Pilha *pilha, char valor);
char desempilhar(Pilha *pilha);
void calculadora(char *equacao, int tamanho);

int main(char equacao[])
{
    setlocale(LC_ALL, "utf-8");
    Pilha pilha;
    inicializar(&pilha);
    do
    {
        prinft("Digite a equação que será calculada: ");
        gets(equacao);
        if (strcmp(equacao, " ") != 0)
        {
        }
    } while (strcmp(equacao, " ") == 0);

    return 0;
}

void inicializar(Pilha *pilha)
{
    pilha->topo = NULL;
}

void empilhar(Pilha *pilha, char valor)
{
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
    {
        printf("Erro de alocação de memória!\n");
        return;
    }
    novo->valor = valor;
    novo->prox = pilha->topo;
    pilha->topo = novo->prox;
}

char desempilhar(Pilha *pilha)
{
    if (pilha == NULL)
    {
        printf("Erro a pilha está vazia!\n");
    }
    else
    {
        No *remover = pilha->topo;
        char valor = remover->valor;
        pilha->topo = pilha->topo->prox;
        free(remover);
        return valor;
    }
}

void calculadora(char *equacao, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        
    }
    strcpy(equacao, " ");
}