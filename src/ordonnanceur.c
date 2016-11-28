#include <ordonnanceur.h>
#include <malloc.c.h>


list_activable* activable = NULL;
processus* elu = NULL;

int NB_PROC = 0;

list_activable* init_list(void)
{
	list_activable* l = malloc(sizeof(list_activable));
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
	elu = proc;
	NB_PROC++;
	
	activable = init_list();
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
	add_queue(activable, proc);
	return NB_PROC++;
}

char* mon_nom(void)
{
	return elu->nom;
}

int mon_pid(void)
{
	return elu->pid;
}

void ordonnance(void)
{
	processus* courant = elu;
	processus* suivant = pop_tete(activable);

	suivant->etat_courant = ELU;
	elu->etat_courant = ACTIVABLE;
	add_queue(activable, elu);
	elu = suivant;

	ctx_sw(courant->sauv_reg, suivant->sauv_reg);
}

void idle(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		sti();
		hlt();
		cli();
	}
}


void proc1(void)
{
	for (;;) {
		printf("[%s] pid = %i\n", mon_nom(), mon_pid());
		sti();
		hlt();
		cli();
	}
}
