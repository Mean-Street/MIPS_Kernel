#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

#include <inttypes.h>

#define TAILLE_PILE 512
#define NB_PROC 2

enum etat = {ELU, ACTIVABLE};

typedef struct processus {
	int32_t pid;
	char[20] nom;
	enum etat etat_courant;
	uint32_t[5] sauv_reg;
	uint32_t[TAILLE_PILE] pile;
} processus;

processus[NB_PROC] TAB_PROC;


void idle(void);
void proc1(void);

#endif
