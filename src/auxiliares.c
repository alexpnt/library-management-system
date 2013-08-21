#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct_list.h"

/* funcao que compara duas datas, devolvendo -1 caso a primeira seja menor, 1 se a segunda for maior ou 0 se forem iguais */
int compara_data(Data d1,Data d2)
{
    int comparacao;

    if(d1.ano<d2.ano)
        comparacao= -1;
    else if(d1.ano>d2.ano)
        comparacao= 1;

    else
    {
        if(d1.mes<d2.mes)
            comparacao= -1;
        else if(d1.mes>d2.mes)
            comparacao= 1;
        else
        {
            if(d1.dia<d2.dia)
                comparacao= -1;
            else if(d1.dia>d2.dia)
                comparacao= 1;
            else
                comparacao= 0;
        }
    }
    return comparacao;
}

/* função que compara uma determinada data com a data de 7 dias atrás em relação à data actual do sistema
   (faz uso da funcao compara_data) */
int sete_dias(Data data)
{
    struct tm *data_aux;
    time_t data_hj,data_7dias;
    Data data_comp;
    data_hj = time(0);
    data_7dias = data_hj - (7*24*3600);
    data_aux = localtime(&data_7dias);

    data_comp.ano = data_aux->tm_year+1900;
    data_comp.mes = data_aux->tm_mon+1;
    data_comp.dia = data_aux->tm_mday;

    return (compara_data(data_comp,data));
}

/* funcao que recebe uma estrutura do tipo Data e a preenche com a data actual do sistema */
void data_actual(Data *d1)
{
    struct tm *ptr_data;
    time_t lt;
    lt = time(0);
    ptr_data=localtime(&lt);

    d1->ano = ptr_data->tm_year+1900;
    d1->mes = ptr_data->tm_mon+1;
    d1->dia = ptr_data->tm_mday;
}

/* funcao que solicita o codigo de um utente, verifica se este existe e devolve um ponteiro para ele na lista ligada */
Utente valida_u(Utente utentes)
{
    int utente_code;
    Utente aux_u;

    do {
    printf("\nIntroduza o codigo do utente: ");
    scanf("%d",&utente_code);
    printf("\n\n");
    } while (getchar()!='\n' || utente_code<1);

    if((aux_u=pesquisa_lista_u(utentes,utente_code)))
        printf("\tNome: %s\n\n",aux_u->registo.nome);

    return aux_u;
}

/* funcao que solicita o codigo de um livro, verifica se este existe e devolve um ponteiro para ele na lista ligada */
Livro valida_l(Livro livros)
{
    int livro_code;
    Livro aux_l;

    do {
    printf("\nIntroduza o codigo do livro: ");
    scanf("%d",&livro_code);
    printf("\n\n");
    } while (getchar()!='\n' || livro_code<1);

    if((aux_l=pesquisa_lista_l(livros,livro_code)))
        printf("\tTitulo: %s\n\n",aux_l->dados.nome);

    return aux_l;
}

/* funcao que solicita o codigo de um livro, verifica se este esta requisitado e devolve um ponteiro para ele na lista ligada */
Requisit valida_r(Requisit requisit)
{
    int livro_code;

    do {
    printf("\nIntroduza o codigo do livro: ");
    scanf("%d",&livro_code);
    printf("\n\n");

    } while (getchar()!='\n' || livro_code<1);

    return (pesquisa_lista_r(requisit,livro_code));
}

/* funcao que mostra a informacao sobre um livro, o seu titulo e se esta requisitado/reservado */
void imprime_info_l(Livro aux_l,Requisit requisit)
{
    Requisit aux_r;
    f_espera aux_fila;

    if(aux_l)
    {
        aux_r = pesquisa_lista_r(requisit,aux_l->dados.cod_livro);

        if(aux_r)
        {
            clear();
            printf("\n\n\n\tInformacao sobre o livro com o titulo: ' %s '\n\n",aux_l->dados.nome);
            printf("+--------------------------------------------------------------+\n");
            printf("| Codigo do utente |  Data de   | Codigo dos utentes em espera |\n");
            printf("| que o requisitou | Requisicao |   com pedido de reserva      |\n");
            printf("+--------------------------------------------------------------+\n");
            printf("%12d         %02d/%02d/%-8d\n\n",aux_r->info.cod_utente,aux_r->info.data_r.dia,aux_r->info.data_r.mes,aux_r->info.data_r.ano);
            aux_fila = aux_r->info.reserva.primeiro;
            while(aux_fila)
            {
                printf("%50d \n\n",aux_fila->cod_utente);

                aux_fila = aux_fila->prox;
            }
        printf("+--------------------------------------------------------------+\n\n\n");
        }
        else printf("\tTitulo: %s\n\n\tO livro nao se encontra requisitado.\n\n\n",aux_l->dados.nome);
    }

    else
        printf("\n\tO livro com esse codigo nao existe.\n\n\n");
}


/* funcao que imprime os livros requisitados ou reservados de um utente */
int historial_u(Requisit requisit,Livro livros,int utente_code,int opcao)
{
    Livro aux_l;
    Requisit aux_r;
    f_espera aux_fila;
    int existe=0,conta=0;

    aux_r = requisit->prox;

    if (opcao==1)
        printf("\n\n\tLista de livros requisitados pelo utente:\n\n");

    else if (opcao==2)
        printf("\n\n\tLista de livros reservados pelo utente:\n\n");

     else if (opcao==3)
        printf("\n\n\n\tLista de livros requisitados e reservados pelo utente:\n\n");


    printf("+--------------------------------------------------------------------------------------------+\n");
    printf("| Cod. Livro |                        Nome do Livro                          |      OBS      |\n");
    printf("+--------------------------------------------------------------------------------------------+\n");

    while(aux_r)
    {
        if (opcao==1 || opcao==3)
        {
            if(aux_r->info.cod_utente==utente_code)
            {
                aux_l = pesquisa_lista_l(livros,aux_r->info.cod_livro);
                printf("%9d       %-60s    requisitado\n\n",aux_r->info.cod_livro,aux_l->dados.nome);
                existe=1;
                conta++;
            }
        }

        if (opcao==2 || opcao==3)
        {
            aux_fila = aux_r->info.reserva.primeiro;
            while(aux_fila)
            {
                if(aux_fila->cod_utente==utente_code)
                {
                    aux_l = pesquisa_lista_l(livros,aux_r->info.cod_livro);
                    printf("%9d       %-60s    (reservado)\n\n",aux_l->dados.cod_livro,aux_l->dados.nome);
                    existe=1;
                    conta++;
                }
                aux_fila = aux_fila->prox;
            }
        }
        aux_r=aux_r->prox;
        if(conta==20)
        {
            conta=0;
            pause();
        }
    }
    printf("+--------------------------------------------------------------------------------------------+\n\n\n");
    return existe;
}

/* funcao que verifica se um utente possui vagas para requisitar/reservar mais livros */
int vagas_u(Requisit requisit, int utente_code)
{
    int conta=0;
    Requisit aux_r;
    f_espera aux_fila;

    aux_r = requisit->prox;

    while(aux_r)
    {
        if(aux_r->info.cod_utente==utente_code)
            conta++;

        aux_fila = aux_r->info.reserva.primeiro;
        while(aux_fila)
        {
            if(aux_fila->cod_utente==utente_code)
                conta++;

            aux_fila = aux_fila->prox;
        }
        aux_r=aux_r->prox;
    }

    if(conta<4)
        return 1;

    else return 0;
}

void clear()
{
    #ifdef WIN32
    system("cls");

    #else
    system("clear");

    #endif
}

void pause()
{
    #ifdef WIN32
    system("pause");

    #else
    system("read -p 'Prima qualquer tecla para continuar . . .'");

    #endif
}

void boneco(int tipo)
{
    if(tipo==1)
    {
        #ifdef WIN32
        system("type entrada.txt");

        #else
        system("cat entrada.txt");

        #endif
    }

    else
    {
        #ifdef WIN32
        system("type saida.txt");

        #else
        system("cat saida.txt");

        #endif
    }
}

