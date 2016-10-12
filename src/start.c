#include <cpu.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <console.h>
#include <init_temps.h>

void kernel_start(void)
    // on ne doit jamais sortir de kernel_start
{
	init_traitant_IT(32, traitant_IT_32);
	init_horloge();
	masque_IRQ(0, 1);
	printf("1 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 1\n\n\n");
	printf("2 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 2\n\n\n");
	printf("3 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 3");

	// démasquage des interruptions externes
	sti();

	// boucle d'attente
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

