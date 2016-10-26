#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define TAILLE_PILE 512
#define NB_PROC 2

enum etat {ELU, ACTIVABLE};

typedef struct processus {
	int32_t pid;
	char nom[20];
	enum etat etat_courant;
	int32_t sauv_reg[5];
	int32_t pile[TAILLE_PILE];
} processus;

processus TAB_PROC[NB_PROC];



void init_idle(void);

void init_proc1(void);

void ctx_sw(int32_t* old_reg, int32_t* new_reg);

void idle(void);

void proc1(void);

void ordonnance (void);

#endif
