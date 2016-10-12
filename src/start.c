#include <cpu.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include <console.h>
// on peut s'entrainer a utiliser GDB avec ce code de base
// par exemple afficher les valeurs de x, n et res avec la commande display

// une fonction bien connue
uint32_t fact(uint32_t n)
{
    uint32_t res;
    if (n <= 1) {
        res = 1;
    } else {
        res = fact(n - 1) * n;
    }
    return res;
}

void kernel_start(void)
{
    // on ne doit jamais sortir de kernel_start
	printf("1 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 1\n\n\n");
	printf("2 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 2\n\n\n");
	printf("3 Lorem ipsum dolor sit amet, consectetur adipiscing elit.\nAenean porta laoreet nibh at feugiat.\nPhasellus non urna volutpat, condimentum felis id, vestibulum neque.\nMaecenas consequat justo sit amet justo pellentesque, at bibendum purus porta.\n\nSed in suscipit quam. 3");
    while (1) {
        // cette fonction arrete le processeur
        hlt();
    }
}

