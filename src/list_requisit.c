#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_list.h"

/* Funcionalidades sobre a lista REQUISITADOS/RESERVADOS */

Requisit cria_lista_r(void)
{
    Requisit aux;

    aux = (Requisit) malloc (sizeof (No_requisit));

    if (aux != NULL) {

        aux->info.cod_livro = 0;
        aux->info.cod_utente = 0;
        aux->info.data_r.dia = 0;
        aux->info.data_r.mes = 0;
        aux->info.data_r.ano = 0;

        aux->prox = NULL;
    }
    return aux;
}

Requisit destroi_lista_r(Requisit lista)
{
    Requisit temp_ptr;

    while (lista_vazia_r(lista) == 0)
    {
        temp_ptr = lista;
        lista= lista->prox;
        free (temp_ptr);
    }
    free(lista);
    return NULL;
}

int lista_vazia_r(Requisit lista)
{
    return (lista->prox == NULL ? 1 : 0);
}

int lista_cheia_r(Requisit lista)
{
    return 0;
}

void procura_lista_r(Requisit lista, int chave, Requisit *ant, Requisit *actual)
{
    *ant = lista; *actual = lista->prox;

    while ((*actual) != NULL && (*actual)->info.cod_livro < chave)
    {
        *ant = *actual;
        *actual = (*actual)->prox;
    }

    if ((*actual) != NULL && (*actual)->info.cod_livro != chave)
        *actual = NULL; /* Se elemento não encontrado*/
}

void insere_lista_r(Requisit lista, Requisit_str requisit_aux)
{
    Requisit no;
    Requisit ant, inutil;

    no = (Requisit) malloc (sizeof (No_requisit));

    if (no != NULL)
    {
        no->info = requisit_aux;
        procura_lista_r(lista, requisit_aux.cod_livro, &ant ,&inutil);
        no->prox = ant->prox;
        ant->prox = no;
    }
}

Requisit pesquisa_lista_r(Requisit lista, int chave)
{
    Requisit ant;
    Requisit actual;

    procura_lista_r(lista,chave, &ant, &actual);

    return (actual);
}

void elimina_lista_r(Requisit lista, int chave)
{
    Requisit ant;
    Requisit actual;

    procura_lista_r(lista,chave,&ant,&actual);

    if (actual != NULL)
    {
        ant->prox = actual->prox;
        free(actual);
    }
}

void imprime_lista_r(Requisit lista)
{
    Requisit person = lista->prox;

    clear();

    printf("\n\n\n");
    printf("+-----------------------------------------------------------------------------------------+\n");
    printf("| Codigo dos Livros | Codigo do utente que  |   Data da    |     Codigo do utente em      |\n");
    printf("|   Requisitados    |  possui a requisicao  |  Requisicao  | espera com pedido de reserva |\n");
    printf("+-----------------------------------------------------------------------------------------+\n\n");

    while (person)
    {
        printf("%12d         %12d             %02d/%02d/%-8d", person->info.cod_livro,person->info.cod_utente,person->info.data_r.dia,person->info.data_r.mes,person->info.data_r.ano);
        if(!fila_vazia(&person->info.reserva))
            printf("  %12d",*person->info.reserva.primeiro);
        person=person->prox;
        printf("\n\n\n");
    }
    printf("+-----------------------------------------------------------------------------------------+\n\n\n");
    pause();
}

