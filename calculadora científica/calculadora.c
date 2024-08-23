#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
#include <ctype.h>

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
char topo(Pilha *pilha);
bool estaVazio(Pilha *pilha);
int prioridade(char valor);
void conversorEquacao(char *equacao, Pilha *pilha);
void calculadora(char equacao[], int tamanho);

int main()
{
    setlocale(LC_ALL, "utf-8");
    Pilha pilha;
    inicializar(&pilha);
    char equacao[100];
    do
    {
        printf("Digite a equação na formatação pós-fixa que será calculada: ");
        gets(equacao);
        equacao[strlen(equacao)] = "\0";
        int tamanho = strlen(equacao);
        if (strcmp(equacao, " ") != 0)
        {
            conversorEquacao(equacao, &pilha);
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

char topo(Pilha *pilha)
{
    return pilha->topo;
}

bool estaVazio(Pilha *pilha)
{
    return (pilha->topo == NULL) ? true : false;
}

int prioridade(char valor)
{
    return (valor == '+' || valor == '-') ? 1 : (valor == '*' || valor == '/') ? 2: (valor == '^')? 3: 0;
}

void conversorEquacao(char *equacao, Pilha *pilha)
{
    char posfixa[strlen(equacao)];
    int j = 0;
    for (int i = 0; equacao[i] != '\0'; i++)
    {
        char valor = equacao[i];
        if (isalnum(valor))
        {
            posfixa[j++] = valor;
        }
        else if (valor == '(')
        {
            empilhar(pilha, valor);
        }
        else if (valor == ')')
        {
            while (!estaVazio(pilha) && topo(pilha) != '(')
            {
                posfixa[j++] = desempilhar(pilha);
            }
            desempilhar(pilha);
        }
        else
        {
            while (!estaVazio(pilha) && prioridade(valor) <= prioridade(topo(pilha)))
            {
                posfixa[j++] = desempilhar(pilha);
            }
            empilhar(pilha, valor);
        }
    }

    while (!estaVazio(pilha))
    {
        posfixa[j++] = desempilhar(pilha);
    }

    posfixa[j] = '\0';
    printf("Equação pós-fixa: %s\n", posfixa);
}

void calculadora(char equacao[], int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
    }
    strcpy(equacao, " ");
}