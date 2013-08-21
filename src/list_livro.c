#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_list.h"

/* Funcionalidades sobre a lista LIVRO */

Livro cria_lista_l(void)
{
    Livro aux;

    aux = (Livro) malloc (sizeof (No_livros));

    if (aux != NULL) {

        strcpy(aux->dados.nome,"0");
        aux->dados.cod_livro = 0;

        aux->prox = NULL;
    }
    return aux;
}

Livro destroi_lista_l(Livro lista)
{
    Livro temp_ptr;

    while (lista_vazia_l(lista) == 0)
    {
        temp_ptr = lista;
        lista= lista->prox;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

int lista_vazia_l(Livro lista)
{
    return (lista->prox == NULL ? 1 : 0);
}

int lista_cheia_l(Livro lista)
{
    return 0;
}

void procura_lista_l(Livro lista, int chave, Livro *ant, Livro *actual)
{
    *ant = lista; *actual = lista->prox;

    while ((*actual) != NULL && (*actual)->dados.cod_livro < chave)
    {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    if ((*actual) != NULL && (*actual)->dados.cod_livro != chave)
        *actual = NULL; /* Se elemento não encontrado*/
}

void insere_lista_l(Livro lista, Livro_str livro_aux)
{
    Livro no;
    Livro ant, inutil;

    no = (Livro) malloc (sizeof (No_livros));

    if (no != NULL)
    {
        no->dados = livro_aux;
        procura_lista_l(lista, livro_aux.cod_livro, &ant ,&inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

Livro pesquisa_lista_l(Livro lista, int chave)
{
    Livro ant;
    Livro actual;

    procura_lista_l(lista,chave, &ant, &actual);

    return (actual);
}

void imprime_lista_l(Livro lista)
{
    Livro book = lista->prox;
    int conta=0;

    clear();

    printf("\n\n\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| Codigo do Livro |                       Titulo do Livro                       |\n");
    printf("+-------------------------------------------------------------------------------+\n\n");

    while (book)
    {
        printf("%12d         %-60s\n\n", book->dados.cod_livro,book->dados.nome);
        conta++;

        if(conta==20)
        {
            conta=0;
            pause();
        }
        book=book->prox;
    }
    printf("+-------------------------------------------------------------------------------+\n\n\n");
    pause();
}
