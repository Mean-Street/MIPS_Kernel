#include <ordonnanceur.h>

void idle(void)
{
	printf("[idle]  : Je passe la main à proc1\n");
	ctx_sw();
}


void proc1(void)
{
	printf("[proc1] : idle m'a donné la main\n");
	printf("[proc1] : J'arrete le système\n");
	hlt();
}
