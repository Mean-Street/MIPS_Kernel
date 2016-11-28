#include <cpu.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <console.h>
#include <init_temps.h>
#include <ordonnanceur.h>

void kernel_start(void)
    // on ne doit jamais sortir de kernel_start
{
	init_traitant_IT(32, traitant_IT_32);
	init_horloge();
	masque_IRQ(0, false);
	/* printf("1 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 1\n\n\n"); */
	/* printf("2 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 2\n\n\n"); */
	/* printf("3 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 3"); */

	init_idle("idle");
	cree_processus(proc1, "Process 1");
	cree_processus(proc1, "Process 2");
	cree_processus(proc1, "Process 3");
	cree_processus(proc1, "Process 4");
	cree_processus(proc1, "Process 5");
	cree_processus(proc1, "Process 6");
	cree_processus(proc1, "Process 7");
	cree_processus(proc1, "Process 8");

	// démasquage des interruptions externes
	/* sti(); */

	idle();

	// boucle d'attente
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

