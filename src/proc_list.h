#ifndef PROC_LIST_H
#define PROC_LIST_H

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>

enum etat {ELU, ACTIVABLE, ENDORMI};

typedef struct processus {
	int32_t pid;
	char* nom;
	enum etat etat_courant;
	int32_t sauv_reg[5];
	int32_t* pile;
	struct processus* suiv;
} processus;


typedef struct list_activable {
	int len;
	processus* tete;
	processus* queue;
} list_activable;


typedef struct list_endormi {
	int len;
	processus* tete;
	processus* queue;
} list_endormi;



void add_queue(list_activable* l, processus* proc);

processus* pop_tete(list_activable* l);

void disp_list(list_activable* l);

#endif
