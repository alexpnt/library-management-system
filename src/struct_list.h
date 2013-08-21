#ifndef STRUCT_LIST_H_INCLUDED
#define STRUCT_LIST_H_INCLUDED

#define MAX 100
#define LIMITE 4

typedef struct
{
    int dia;
    int mes;
    int ano;
} Data;

/* FILA DE ESPERA PARA LIVROS RESERVADOS */

typedef struct node_fila
{
    int cod_utente;
    struct node_fila *prox;

} No_fila;

typedef No_fila *f_espera;

typedef struct
{
    No_fila *primeiro;
    No_fila *ultimo;

} Ctrl_fila;

/*Estruturas elementares dos utentes,dos livros e dos requesitados*/
typedef struct
{
    char nome[MAX];
    int cod_livro;

} Livro_str;

typedef struct
{
    char nome[MAX];
    int cod_utente;

} Utente_str;

typedef struct
{
    int cod_livro;
    int cod_utente;
    Data data_r;
    Ctrl_fila reserva;

} Requisit_str;


/* LISTA LIGADA DE LIVROS */

typedef struct no_l *Livro;

typedef struct no_l
{
    Livro_str dados;
    Livro prox;

} No_livros;

/* LISTA LIGADA DE UTENTES */

typedef struct no_u *Utente;

typedef struct no_u
{
    Utente_str registo;
    Utente prox;

} No_utentes;

/* LISTA LIGADA DE REQUISITADOS/RESERVADOS */

typedef struct no_r *Requisit;

typedef struct no_r
{
    Requisit_str info;
    Requisit prox;

} No_requisit;


void constroi(Livro,Utente,Requisit);
int compara_data(Data,Data);
void requisitar(Livro,Utente,Requisit);
void devolver(Requisit,Livro,Utente);
void cancelar_reserva(Requisit,Livro,Utente);
void data_actual(Data*);
void livros_atraso(Requisit,Livro,Utente);
int sete_dias(Data);
char menu(char**);
Utente valida_u(Utente);
Livro valida_l(Livro);
Requisit valida_r(Requisit);
int vagas_u(Requisit,int);
void gravar_fich(Requisit,int);
int historial_u(Requisit,Livro,int,int);
void submenu(Requisit,Livro,Utente);
void imprime_info_l(Livro,Requisit);
void pause();
void clear();
void boneco(int);


Utente cria_lista_u();
Utente destroi_lista_u(Utente);
int lista_vazia_u(Utente);
int lista_cheia_u(Utente);
void procura_lista_u(Utente,int,Utente *,Utente *);
void insere_lista_u(Utente,Utente_str);
Utente pesquisa_lista_u(Utente,int);
void imprime_lista_u(Utente);

Livro cria_lista_l();
Livro destroi_lista_l(Livro);
int lista_vazia_l(Livro);
void procura_lista_l(Livro, int, Livro *, Livro *);
void insere_lista_l(Livro, Livro_str);
Livro pesquisa_lista_l(Livro, int);
void imprime_lista_l(Livro);

Requisit cria_lista_r();
Requisit destroi_lista_r(Requisit);
int lista_vazia_r(Requisit);
int lista_cheia_r(Requisit);
void procura_lista_r(Requisit,int, Requisit *,Requisit *);
void insere_lista_r(Requisit, Requisit_str);
Requisit pesquisa_lista_r(Requisit,int);
void elimina_lista_r(Requisit,int);
void imprime_lista_r(Requisit);

void cria_fila(Ctrl_fila *);
void destroi_fila(Ctrl_fila *);
int fila_vazia(Ctrl_fila *);
int fila_cheia(Ctrl_fila *);
void coloca(Ctrl_fila *, int);
int retira(Ctrl_fila *);



#endif /* STRUCT_LIST_H_INCLUDED */
