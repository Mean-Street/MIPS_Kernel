#include <ordonnanceur.h>
#include <malloc.c.h>
#include <string.h>
#include <cpu.h>

/* processus* TAB_PROC[NB_PROC_MAX]; */

proc_list* liste_activable = NULL;
processus* elu = NULL;

/* int PROC_CURR = 0; */
int NB_PROC = 0;

proc_list* init_list(void)
{
	proc_list* l = malloc(sizeof(proc_list));
	l->len = 0;
	l->tete = NULL;
	l->queue = NULL;
	return l;
}


void init_idle(char* nom)
{
	processus* proc = malloc(sizeof(processus));
	proc->pid = 0;
	proc->nom = malloc(sizeof(strlen(nom) + 1));
	strcpy(proc->nom, nom);
	proc->etat_courant = ELU;
	/* TAB_PROC[PROC_CURR] = proc; */
	elu = proc;
	NB_PROC++;

	liste_activable = init_list();
}

int32_t cree_processus(void (*code)(void), char* nom)
{
	if (NB_PROC == NB_PROC_MAX || nom == NULL) {
		return -1;
	}
	processus* proc = malloc(sizeof(processus));
	proc->pile = malloc(sizeof(int)*TAILLE_PILE);
	proc->pid = NB_PROC;
	proc->nom = malloc(sizeof(strlen(nom) + 1));
	strcpy(proc->nom, nom);
	proc->etat_courant = ACTIVABLE;
	proc->sauv_reg[1] = (int32_t)&(proc->pile[TAILLE_PILE-1]);
	proc->pile[TAILLE_PILE-1] = (int32_t)code;
	/* TAB_PROC[NB_PROC] = proc; */
	add_queue(liste_activable, proc);
	return NB_PROC++;
}

char* mon_nom(void)
{
	/* return TAB_PROC[PROC_CURR]->nom; */
	return elu->nom;
}

int mon_pid(void)
{
	/* return TAB_PROC[PROC_CURR]->pid; */
	return elu->pid;
}

void ordonnance(void)
{
	/* int curr = PROC_CURR; */
	/* int suiv = (PROC_CURR + 1) % NB_PROC; */
	/* printf("%d -> %d\n", curr, suiv); */
	processus* courant = elu;
	processus* suivant = pop_tete(liste_activable);

	suivant->etat_courant = ELU;
	elu->etat_courant = ACTIVABLE;
	add_queue(liste_activable, elu);
	elu = suivant;

	/* TAB_PROC[curr]->etat_courant = ACTIVABLE; */
	/* TAB_PROC[suiv]->etat_courant = ELU; */
	/* PROC_CURR = suiv; */
	/* ctx_sw(TAB_PROC[curr]->sauv_reg, TAB_PROC[suiv]->sauv_reg); */
	ctx_sw(courant->sauv_reg, suivant->sauv_reg);
}

void idle(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		ordonnance();
	}
}


void proc1(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		ordonnance();
	}
}
