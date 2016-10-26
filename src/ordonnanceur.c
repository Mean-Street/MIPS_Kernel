#include <ordonnanceur.h>
#include <string.h>
#include <cpu.h>


void init_idle(processus* tab_proc)
{
	tab_proc[0].pid = 0;
	strcpy(tab_proc[0].nom, "idle");
	tab_proc[0].etat_courant = ELU;
}

void init_proc1(processus* tab_proc)
{
	tab_proc[1].pid = 1;
	strcpy(tab_proc[1].nom, "proc1");
	tab_proc[1].etat_courant = ACTIVABLE;
	tab_proc[1].sauv_reg[1] = (int32_t)&(tab_proc[1].pile[TAILLE_PILE-1]);
	tab_proc[1].pile[TAILLE_PILE-1] = (int32_t)proc1;
}

void idle(void)
{
	for (int i = 0; i < 3; i++) {
		printf("[idle]  : Je passe la main à proc1\n");
		ctx_sw(TAB_PROC[0].sauv_reg, TAB_PROC[1].sauv_reg);
		printf("[idle]  : proc1 m'a rendu la main\n");
	}
	printf("[idle]  : Je bloque le systeme\n");
	hlt();
}


void proc1(void)
{
	for (;;) {
		printf("[proc1] : idle m'a donné la main\n");
		ctx_sw(TAB_PROC[1].sauv_reg, TAB_PROC[0].sauv_reg);
	}
}
