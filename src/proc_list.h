#ifndef PROC_LIST_H
#define PROC_LIST_H

#include <inttypes.h>
#include <stdio.h>
#include <stddef.h>

enum etat {ELU, ACTIVABLE};

typedef struct processus {
	int32_t pid;
	char* nom;
	enum etat etat_courant;
	int32_t sauv_reg[5];
	int32_t* pile;
	struct processus* suiv;
} processus;

typedef struct proc_list {
	int len;
	processus* tete;
	processus* queue;
} proc_list;



void add_queue(proc_list* l, processus* proc);

processus* pop_tete(proc_list* l);

void disp_list(proc_list* l);

#endif
