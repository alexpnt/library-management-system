#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_list.h"

void cria_fila(Ctrl_fila *fila)
{
	fila->primeiro = NULL;
	fila->ultimo= NULL;
}

void destroi_fila(Ctrl_fila *fila)
{
	f_espera temp;
	while (fila_vazia(fila) == 0)
	{
		temp =fila->primeiro;
		fila->primeiro=fila->primeiro->prox;
		free (temp);
	}
	fila->ultimo= NULL;
}

int fila_vazia(Ctrl_fila *fila)
{
	return (fila->primeiro== NULL ? 1 : 0);
}

int fila_cheia(Ctrl_fila *fila)
{
	return 0;
}

void coloca(Ctrl_fila *fila, int code)
{
	f_espera temp;
	temp = (f_espera) malloc (sizeof (No_fila));
	if (temp != NULL)
	{
		temp->cod_utente = code;
		temp->prox = NULL;

		if (fila_vazia(fila) == 1)
			fila->primeiro = temp;

		else fila->ultimo->prox = temp;
		fila->ultimo = temp;
	}
}

int retira(Ctrl_fila *fila)
{
	f_espera temp;
	int code;
	if (fila_vazia(fila) == 0)
	{
		temp = fila->primeiro;
		code = temp->cod_utente;
		fila->primeiro = fila->primeiro->prox;
		if (fila_vazia(fila) == 1)
			fila->ultimo = NULL;
		free (temp);
		return (code);
	}
	return 0;
}
