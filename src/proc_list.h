#ifndef PROC_LIST_H
#define PROC_LIST_H

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>

enum etat {ELU, ACTIVABLE, ENDORMI, MOURANT};

typedef struct processus {
	int32_t pid;
	char* nom;
	enum etat etat_courant;
	int32_t sauv_reg[5];
	int32_t* pile;
	struct processus* suiv;
	uint32_t temps_reveil;
} processus;


/* Liste des processus activables  */
typedef struct list_activable {
	int len;
	processus* tete;
	processus* queue;
} list_activable;

void add_queue(list_activable* l, processus* proc);

processus* pop_tete(list_activable* l);

void disp_list_activable(list_activable* l);


/* Liste des processus endormis */
typedef struct list_endormi {
	int len;
	processus* tete;
} list_endormi;

void add_elt(list_endormi* l, processus* proc, uint32_t temps_reveil);

bool is_empty(list_endormi* l);

uint32_t get_prio(list_endormi* l);

processus* pop_prio(list_endormi* l);

void disp_list_endormi(list_endormi* l);


/* Liste des processus mourants */
typedef struct list_mourant {
	processus* tete;
} list_mourant;

void add_mourant(list_mourant* l, processus* proc);


#endif
