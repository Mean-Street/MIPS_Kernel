#include <ordonnanceur.h>
#include <malloc.c.h>


list_activable* L_ACTIVABLE = NULL;
list_endormi* L_ENDORMI = NULL;
processus* PROC_ELU = NULL;

int NB_PROC = 0;
int TIME_INIT;

uint32_t nbr_secondes(void) {
	return TOTAL_TIME;
}

list_activable* init_list_activable(void)
{
	list_activable* l = malloc(sizeof(list_activable));
	l->len = 0;
	l->tete = NULL;
	l->queue = NULL;
	return l;
}

list_endormi* init_list_endormi(void)
{
	list_endormi* l = malloc(sizeof(list_endormi));
	l->len = 0;
	l->tete = NULL;
	return l;
}


void init_idle(char* nom)
{
	processus* proc = malloc(sizeof(processus));
	proc->pid = 0;
	proc->nom = malloc(sizeof(strlen(nom) + 1));
	strcpy(proc->nom, nom);
	proc->etat_courant = ELU;
	PROC_ELU = proc;
	NB_PROC++;
	
	L_ACTIVABLE = init_list_activable();
	L_ENDORMI = init_list_endormi();
	TIME_INIT = 0;
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
	proc->temps_reveil = 0;
	add_queue(L_ACTIVABLE, proc);
	return NB_PROC++;
}

char* mon_nom(void)
{
	return PROC_ELU->nom;
}

int mon_pid(void)
{
	return PROC_ELU->pid;
}

void ordonnance(void)
{
	while (!is_empty(L_ENDORMI) && get_prio(L_ENDORMI) <= TOTAL_TIME) {
		add_queue(L_ACTIVABLE, pop_prio(L_ENDORMI));
	}
	processus* courant = PROC_ELU;

	PROC_ELU = pop_tete(L_ACTIVABLE);

	if (PROC_ELU != NULL) {
		// si on a récupéré un activable, on le rend actif
		add_queue(L_ACTIVABLE, courant);
		ctx_sw(courant->sauv_reg, PROC_ELU->sauv_reg);
	} else {
		// si personne dans les activables, le courant continue
		PROC_ELU = courant;
	}
}

void dors(uint32_t nbr_secs) {
	processus* courant = PROC_ELU;
	add_elt(L_ENDORMI, PROC_ELU, TOTAL_TIME + nbr_secs);
	PROC_ELU = pop_tete(L_ACTIVABLE);
	ctx_sw(courant->sauv_reg, PROC_ELU->sauv_reg);
}

void idle(void)
{
	for (;;) {
		/* printf("[%s] pid = %i\n", mon_nom(), mon_pid()); */
		sti();
		hlt();
		cli();
	}
}

void proc1(void)
{
	for (;;) {
		printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
		dors(2);
	}
}

void proc2(void)
{
	for (;;) {
		printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
		dors(3);
	}
}

void proc3(void)
{
	for (;;) {
		printf("[temps = %u] processus %s pid = %i\n", nbr_secondes(), mon_nom(), mon_pid());
		dors(5);
	}
}
