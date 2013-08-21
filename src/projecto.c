 /* --------------------------------------Mini-Projecto - 2010/2011 ------------------------------
    Alexandre Pinto,    LEI,2010131853
    Carlos Miguel Avim, LEI,2000104864
 ------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "struct_list.h"

#define MAX 100
#define LIMITE 4

#define DEVOLVER    '1'
#define REQUISITAR  '2'
#define CANCELAR    '3'
#define LISTAR      '4'
#define INFO        '5'
#define SAIR        '0'

int main()
{
    char opcao;
    char *opcoes_menu[]={
    "1. Devolver Livro",
    "2. Requisitar Livro",
    "3. Cancelar Reserva",
    "4. Listar Livros com Entrega em Atraso",
    "5. Informacoes",
    "0. Sair",
    NULL };

    Livro livros;
    Utente utentes;
    Requisit requisit;

    livros = cria_lista_l();
    utentes = cria_lista_u();
    requisit = cria_lista_r();

    constroi(livros,utentes,requisit);
    clear();
    boneco(1);
    pause();

    while((opcao=menu(opcoes_menu))!=SAIR)
        switch (opcao)
        {
            case DEVOLVER:
            {
                clear();
                devolver(requisit,livros,utentes);
                pause();
                break;
            }

            case REQUISITAR:
            {
                clear();
                requisitar(livros,utentes,requisit);
                pause();
                break;
            }

            case CANCELAR:
            {
                clear();
                cancelar_reserva(requisit,livros,utentes);
                pause();
                break;
            }

            case LISTAR:
            {
                clear();
                livros_atraso(requisit,livros,utentes);
                pause();
                break;
            }

            case INFO:
            {
                clear();
                submenu(requisit,livros,utentes);
                break;
            }
        }

    destroi_lista_l(livros);
    destroi_lista_u(utentes);
    destroi_lista_r(requisit);

    clear();
    boneco(2);
    pause();

    return 0;
}

void constroi(Livro livros, Utente utentes, Requisit requisit)
{
    int aux,teste;
    char nome_aux[MAX];
    Livro_str livro_aux;
    Utente_str utente_aux;
    Requisit_str requisit_aux;
    FILE *livro_f, *utente_f, *requisit_f;

    livro_f = fopen("livros.txt","r");
    utente_f = fopen("utentes.txt","r");
    requisit_f = fopen("requisit.txt","r+");

    /* Ler dados do ficheiro livros.txt para a lista ligada Livro */
    while(1)
    {
        fgets(nome_aux,MAX,livro_f);
        aux = strlen(nome_aux);
        nome_aux[aux-1] = '\0';
        strcpy(livro_aux.nome,nome_aux);
        if(fscanf(livro_f,"%d",&livro_aux.cod_livro)!=1)
        {
            printf("Houve um erro na leitura do ficheiro livros.txt\n\n");
			pause();
            exit(1);
        }

        insere_lista_l(livros,livro_aux);

        if(fscanf(livro_f,"%d",&aux)==EOF)
            break;
    }


/* Ler dados do ficheiro utentes.txt para a lista ligada Utente */
    while(1)
    {
        fgets(nome_aux,MAX,utente_f);
        if(!(aux = strlen(nome_aux)))
        {
            printf("Houve um erro na leitura do ficheiro utentes.txt\n\n");
			pause();
            exit(1);
        }
        nome_aux[aux-1] = '\0';
        strcpy(utente_aux.nome,nome_aux);
        if(fscanf(utente_f,"%d",&utente_aux.cod_utente)!=1)
        {
            printf("Houve um erro na leitura do ficheiro utentes.txt\n\n");
			pause();
            exit(1);
        }

        insere_lista_u(utentes,utente_aux);

        if(fscanf(utente_f,"%d",&aux)==EOF)
            break;
    }


/* Ler dados do ficheiro requisit.txt para a lista ligada Requisit */
    while(1)
    {
        if((teste=fscanf(requisit_f,"%d",&requisit_aux.cod_livro))!=1 && teste!=-1)
        {
            printf("Houve um erro na leitura do ficheiro requisit.txt\n\n");
			pause();
            exit(1);
        }
        if (teste!=-1)
        {
            if(fscanf(requisit_f,"%d",&requisit_aux.cod_utente)!=1)
            {
                printf("Houve um erro na leitura do ficheiro requisit.txt\n\n");
                pause();
                exit(1);
            }
            if(fscanf(requisit_f,"%d/%d/%d",&requisit_aux.data_r.dia,&requisit_aux.data_r.mes,&requisit_aux.data_r.ano)!=3)
            {
                printf("Houve um erro na leitura do ficheiro requisit.txt\n\n");
                pause();
                exit(1);
            }

            cria_fila(&(requisit_aux.reserva));

            while(1)
            {
                if(fscanf(requisit_f,"%d",&aux)!=1)
                {
                    printf("Houve um erro na leitura do ficheiro requisit.txt\n\n");
                    pause();
                    exit(1);
                }
                if (aux!=0)
                    coloca(&(requisit_aux.reserva),aux);
                else break;
            }

            insere_lista_r(requisit,requisit_aux);

            if((fgetc(requisit_f)==EOF))
                break;
        }
        else break;
    }

    fclose(livro_f);
    fclose(utente_f);
    fclose(requisit_f);

}

/* funcao para processar a requisicao de um livro */
void requisitar(Livro livros, Utente utentes,Requisit requisit)
{
    int reserva=1,valido=1;
    char opcao;
    Utente aux_u;
    Livro aux_l;
    Requisit aux_r;
    Requisit_str req_aux;
    f_espera aux_fila;

    while (valido==1)
    {
        if(!(aux_u = valida_u(utentes)))
        {
            printf("O codigo de utente introduzido nao existe!\n\n\n");
            valido=0;
            break;
        }

        if(!vagas_u(requisit,aux_u->registo.cod_utente))
        {
            printf("\n\nO utente ja atingiu o limite de requisicoes/reservas!\n\n\n");
            valido=0;
            break;
        }

        if(!(aux_l = valida_l(livros)))
        {
            printf("O codigo do livro introduzido nao existe!\n\n\n");
            valido=0;
            break;
        }

        if((aux_r = pesquisa_lista_r(requisit,aux_l->dados.cod_livro)))
        {
            printf("\n\nO livro encontra-se requisitado!\n\n\n");

            aux_fila = aux_r->info.reserva.primeiro;
            while(aux_fila)
            {
                if(aux_fila->cod_utente==aux_u->registo.cod_utente)
                {
                    printf("O utente ja possui um pedido de reserva para este livro!\n\n\n");
                    reserva=0;
                }

                aux_fila = aux_fila->prox;
            }

            if(reserva==1)
            {
                do {
                printf("Pretende reservar o livro? (S/N): ");
                printf("\n");
                opcao=getchar();
                opcao=toupper(opcao);
                } while (opcao!='S' && opcao != 'N');

                if(opcao=='S')
                {
                    coloca(&aux_r->info.reserva,aux_u->registo.cod_utente);
                    printf("\nO livro foi reservado com sucesso!\n\n\n");
                    gravar_fich(requisit,0);
                    printf("\n\nInformacao guardada em disco.\n\n\n");
                }
            }
            valido=0;
            break;
        }
        break;
    }

    if(valido==1)
    {
        req_aux.cod_livro = aux_l->dados.cod_livro;
        req_aux.cod_utente = aux_u->registo.cod_utente;
        data_actual(&req_aux.data_r);

        cria_fila(&(req_aux.reserva));
        insere_lista_r(requisit,req_aux);

        printf("\n\nO livro foi requisitado com sucesso!\n\n");
        gravar_fich(requisit,aux_l->dados.cod_livro);
        printf("\n\nInformacao guardada em disco.\n\n\n");
    }
}

/* funcao para processar a devolucao de um livro */
void devolver(Requisit requisit,Livro livros,Utente utentes)
{
    Requisit aux_r;
    Utente aux_u;
    int utente_code;

    if((aux_u=valida_u(utentes)))
    {
        utente_code = aux_u->registo.cod_utente;
        if(!(historial_u(requisit,livros,utente_code,1)))
            printf("O utente nao possui livros requisitados!\n\n\n");

        else if((aux_r = valida_r(requisit)))
        {
            if((utente_code=retira(&aux_r->info.reserva)))
            {
                aux_r->info.cod_utente = utente_code;
                data_actual(&aux_r->info.data_r);
                printf("Este livro foi devolvido com sucesso e automaticamente requisitado \npelo utente com o codigo n. %d, que se encontrava em lista de espera.\n\n\n",utente_code);
            }

            else
            {
                elimina_lista_r(requisit,aux_r->info.cod_livro);
                printf("O livro foi devolvido com sucesso!\n\n\n");
            }

            gravar_fich(requisit,0);
            printf("\n\nInformacao guardada em disco.\n\n\n");
        }
    }
    else printf("Esse utente nao existe!\n\n\n");
}

/* funcao para cancelar uma reserva de um livro na fila de espera */
void cancelar_reserva(Requisit requisit,Livro livros,Utente utentes)
{
    int utente_code,sucesso=0,possui=1;
    Requisit aux_r;
    Utente aux_u;
    f_espera aux_fila,ant;

    if((aux_u = valida_u(utentes)))
    {
        utente_code = aux_u->registo.cod_utente;

        if(!(historial_u(requisit,livros,utente_code,2)))
        {
            printf("O utente nao possui reservas!\n\n\n");
            possui=0;
        }


        else if((aux_r=valida_r(requisit)))
        {
            aux_fila = aux_r->info.reserva.primeiro;
            while(aux_fila)
            {
                if(aux_fila->cod_utente==utente_code)
                {
                    if(aux_fila==aux_r->info.reserva.primeiro) /* caso o elemento a retirar estiver em primeiro */
                    {
                        retira(&aux_r->info.reserva);
                        sucesso=1;
                        break;
                    }
                                                                /* caso o elemento a retirar esteja em ultimo */
                    else if(aux_fila == aux_r->info.reserva.ultimo)
                    {
                        aux_r->info.reserva.ultimo = ant;
                        free(aux_fila);
                        sucesso=1;
                        break;

                    }

                    else            /* caso o elemento a retirar nao esteja em primeiro nem ultimo */
                    {
                        ant->prox = aux_fila->prox;
                        free(aux_fila);
                        sucesso=1;
                        break;
                    }
                }
                ant = aux_fila;
                aux_fila = aux_fila->prox;
            }
        }
        if(sucesso==1)
        {
            printf("Reserva cancelada com sucesso!\n\n\n");
            gravar_fich(requisit,0);
            printf("\n\nInformacao guardada em disco.\n\n\n");
        }
        else if(possui)
            printf("O codigo do livro introduzido nao esta reservado pelo utente!\n\n\n");
    }
    else printf("Esse utente nao existe!\n\n\n");
}

/* funcao que imprime a listagem dos livros requisitados em atraso (mais de 7 dias) */
void livros_atraso(Requisit requisit,Livro livros,Utente utentes)
{
    int i=0,comp,j,pass,trocou = 1;
    Requisit aux,temp,*enderecos;
    Livro aux_l;
    Utente aux_u;

    enderecos = (Requisit*)malloc(sizeof(No_requisit));

    aux = requisit->prox;

    while(aux)
    {
        if(sete_dias(aux->info.data_r)==1)
           {
               *(enderecos+i)=&(*aux);
               i++;
               enderecos = (Requisit*)realloc(enderecos,(i+1)*sizeof(No_requisit));
           }
            aux=aux->prox;
    }

    for (pass=0; pass<i-1 && trocou; pass++)        /* metodo de bubble sort para ordenar o vector de enderecos*/
    {
        trocou = 0;
        for (j = 0; j < i-pass-1; j++)
        {
            comp=compara_data(enderecos[j]->info.data_r,enderecos[j+1]->info.data_r);

            if (comp==1)
            {
                trocou = 1;
                temp = enderecos[j];
                enderecos[j] = enderecos[j+1];
                enderecos[j+1] = temp;
            }
        }
    }
    clear();
    printf("\n\n\n\tOs livros em atraso (mais de 7 dias) sao os seguintes:\n\n");
    printf("+--------------------------------------------------------------------------------------------------------------------------+\n");
    printf("|C.Livro|                     Nome do Livro                        |Data Requisic |C.Utente|          Nome Utente          |\n");
    printf("+--------------------------------------------------------------------------------------------------------------------------+\n");
    for(j=0;j<i;j++)
    {
        aux_l = pesquisa_lista_l(livros,enderecos[j]->info.cod_livro);
        aux_u = pesquisa_lista_u(utentes,enderecos[j]->info.cod_utente);
        printf("%6d    %-58s  %02d/%02d/%-7d     %-5d  %-27s\n\n",enderecos[j]->info.cod_livro,aux_l->dados.nome,enderecos[j]->info.data_r.dia,enderecos[j]->info.data_r.mes,enderecos[j]->info.data_r.ano,enderecos[j]->info.cod_utente,aux_u->registo.nome);
    }
    printf("+--------------------------------------------------------------------------------------------------------------------------+\n\n\n");

    free(enderecos);
}
/* menu principal do programa para escolha da opcao pretendida */
char menu(char *opcoes_menu[])
{
    int i;
    char opcao;
    while(1)
    {
        clear();
        printf("\n\n\t* * * * *   P R O G R A M A   D E   G E S T A O   D E   L I V R O S   * * * * *\n\n\n\n\n\n");
        printf("\t- - - - -  M E N U  - - - - -\n\n\n\n");
        for(i=0;opcoes_menu[i];i++)
            printf("\t%s\n\n",opcoes_menu[i]);

        printf("\n\n\tEscolha a opcao pretendida: ");
        fflush(stdin);
        opcao = getchar();
        printf("\n\n");


        for(i=0;opcoes_menu[i];i++)
        {
            if(opcoes_menu[i][0]==opcao)
                return opcao;
        }
    }
}

void submenu(Requisit requisit,Livro livros,Utente utentes)
{
    char opcao;
    int sair=1;
    Livro aux_l;
    Utente aux_u;
    int utente_code;

    while(sair)
    {
        clear();
        printf("\n\n\n\t- - -  OPCOES  - - -\n\n\n\n");
        printf("\t1. Listar os livros requisitados/reservados.\n\n");
        printf("\t2. Listar os livros existentes.\n\n");
        printf("\t3. Listar os utentes existentes.\n\n");
        printf("\t4. Ver informacoes sobre um utente.\n\n");
        printf("\t5. Ver informacoes sobre um livro.\n\n");
        printf("\t0. Voltar ao menu anterior.\n\n\n");
        printf("\tEscolha a opcao pretendida: ");
        fflush(stdin);
        opcao = getchar();

        switch(opcao)
        {
            case '1': imprime_lista_r(requisit); break;
            case '2': imprime_lista_l(livros); break;
            case '3': imprime_lista_u(utentes); break;
            case '4':
            {
                if((aux_u = valida_u(utentes)))
                {
                    utente_code = aux_u->registo.cod_utente;
                    historial_u(requisit,livros,utente_code,3);
                }
                else printf("Esse utente nao existe!\n\n\n");
                pause(); break;
            }
            case '5':
            {
                aux_l=valida_l(livros);
                imprime_info_l(aux_l,requisit);
                pause();
                break;
            }
            case '0':sair=0;break;
            default: continue;break;
        }
    }
}

void gravar_fich(Requisit requisit, int code)
{
    FILE *requisit_f;
    Requisit aux_r;
    f_espera aux_fila;

    if(code)
    {
        requisit_f = fopen("requisit.txt","a");

        aux_r = pesquisa_lista_r(requisit,code);

        if (lista_vazia_r(requisit->prox)==0)
            fprintf(requisit_f,"\n\n");

        fprintf(requisit_f,"%d\n",aux_r->info.cod_livro);
        fprintf(requisit_f,"%d\n",aux_r->info.cod_utente);
        fprintf(requisit_f,"%d/%d/%d\n",aux_r->info.data_r.dia,aux_r->info.data_r.mes,aux_r->info.data_r.ano);
        fprintf(requisit_f,"0");

        fclose(requisit_f);
    }

    else
    {
        requisit_f = fopen("requisit.txt","w");
        aux_r=requisit->prox;

        while(aux_r)
        {
            fprintf(requisit_f,"%d\n",aux_r->info.cod_livro);
            fprintf(requisit_f,"%d\n",aux_r->info.cod_utente);
            fprintf(requisit_f,"%d/%d/%d\n",aux_r->info.data_r.dia,aux_r->info.data_r.mes,aux_r->info.data_r.ano);

            aux_fila = aux_r->info.reserva.primeiro;
            while(aux_fila)
            {
                fprintf(requisit_f,"%d ",aux_fila->cod_utente);
                aux_fila = aux_fila->prox;
            }
            if(aux_r->prox!=NULL)
               fprintf(requisit_f,"0\n\n");
            else fprintf(requisit_f,"0");
            aux_r=aux_r->prox;
        }
        fclose(requisit_f);
    }
}
