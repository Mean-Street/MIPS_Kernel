#include <proc_list.h>

void add_queue(proc_list* l, processus* proc)
{
	proc->suiv = NULL;
	if (l->len == 0) {
		l->tete = proc;
	} else {
		l->queue->suiv = proc;
	}
	l->queue = proc;
	l->len++;
}


processus* pop_tete(proc_list* l)
{
	if (l->len == 0)
		return NULL;
	
	processus* tmp = l->tete;
	if (l->len == 1) {
		l->tete = NULL;
		l->queue = NULL;
	} else {
		l->tete = tmp->suiv;
	}
	l->len--;
	return tmp;
}


void disp_list(proc_list* l) {
	processus* tmp = l->tete;
	printf("Len = %d\n", l->len);
	while (tmp != NULL) {
		printf("%s, ", tmp->nom);
		tmp = tmp->suiv;
	}
	printf("\n");
}

