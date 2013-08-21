#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_list.h"

#define LIMITE 4

/* Funcionalidades sobre a lista UTENTE */

Utente cria_lista_u(void)
{
    Utente aux;
    aux = (Utente) malloc (sizeof (No_utentes));

    if (aux != NULL) {
        strcpy(aux->registo.nome,"0");
        aux->registo.cod_utente = 0;

        aux->prox = NULL;
    }
    return aux;
}

Utente destroi_lista_u(Utente lista)
{
    Utente temp_ptr;

    while (lista_vazia_u(lista) == 0)
    {
        temp_ptr = lista;
        lista= lista->prox;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

int lista_vazia_u(Utente lista)
{
    return (lista->prox == NULL ? 1 : 0);
}

int lista_cheia_u(Utente lista)
{
    return 0;
}

void procura_lista_u(Utente lista, int chave, Utente *ant, Utente *actual)
{
    *ant = lista; *actual = lista->prox;

    while ((*actual) != NULL && (*actual)->registo.cod_utente < chave)
    {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    if ((*actual) != NULL && (*actual)->registo.cod_utente != chave)
        *actual = NULL; /* Se elemento não encontrado*/
}

void insere_lista_u(Utente lista, Utente_str utente_aux)
{
    Utente no;
    Utente ant, inutil;

    no = (Utente) malloc (sizeof (No_utentes));

    if (no != NULL)
    {
        no->registo = utente_aux;

        procura_lista_u(lista, utente_aux.cod_utente, &ant, &inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

Utente pesquisa_lista_u(Utente lista, int chave)
{
    Utente ant;
    Utente actual;

    procura_lista_u(lista,chave, &ant, &actual);

    return (actual);
}

void imprime_lista_u(Utente lista)
{
    int conta=0;

    Utente person = lista->prox;

    clear();

    printf("\n\n\n");
    printf("+-------------------------------------------------------------------------------+\n");
    printf("| Codigo do Utente |                       Nome do Utente                       |\n");
    printf("+-------------------------------------------------------------------------------+\n\n");

    while (person)
    {
        printf("%12d            %-60s\n\n", person->registo.cod_utente,person->registo.nome);
        conta++;

        if(conta==20)
        {
            conta=0;
            pause();
        }

        person=person->prox;
    }
    printf("+-------------------------------------------------------------------------------+\n\n\n");
    pause();
}
