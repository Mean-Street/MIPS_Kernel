#include <ordonnanceur.h>
#include <string.h>
#include <cpu.h>

processus TAB_PROC[NB_PROC];

int PROC_CURR;

void init_idle(void)
{
	TAB_PROC[0].pid = 0;
	strcpy(TAB_PROC[0].nom, "idle");
	TAB_PROC[0].etat_courant = ELU;
	PROC_CURR = 0;
}

void init_proc1(void)
{
	TAB_PROC[1].pid = 1;
	strcpy(TAB_PROC[1].nom, "proc1");
	TAB_PROC[1].etat_courant = ACTIVABLE;
	TAB_PROC[1].sauv_reg[1] = (int32_t)&(TAB_PROC[1].pile[TAILLE_PILE-1]);
	TAB_PROC[1].pile[TAILLE_PILE-1] = (int32_t)proc1;
}

char* mon_nom(void)
{
	return TAB_PROC[PROC_CURR].nom;
}

int mon_pid(void)
{
	return TAB_PROC[PROC_CURR].pid;
}

void ordonnance(void)
{
	int curr = PROC_CURR;
	int suiv = (PROC_CURR + 1) % NB_PROC;
	TAB_PROC[curr].etat_courant = ACTIVABLE;
	TAB_PROC[suiv].etat_courant = ELU;
	PROC_CURR = suiv;
	ctx_sw(TAB_PROC[curr].sauv_reg, TAB_PROC[suiv].sauv_reg);
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
