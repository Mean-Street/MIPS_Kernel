#include <proc_list.h>

void add_queue(list_activable* l, processus* proc)
{
	proc->etat_courant = ACTIVABLE;
	proc->suiv = NULL;
	if (l->len == 0) {
		l->tete = proc;
	} else {
		l->queue->suiv = proc;
	}
	l->queue = proc;
	l->len++;
}


processus* pop_tete(list_activable* l)
{
	if (l->len == 0)
		return NULL;
	
	processus* tmp = l->tete;
	l->tete = tmp->suiv;
	if (l->len == 1)
		l->queue = NULL;
	l->len--;
	tmp->etat_courant = ELU;
	return tmp;
}


void disp_list(list_activable* l) {
	processus* tmp = l->tete;
	printf("Len = %d\n", l->len);
	while (tmp != NULL) {
		printf("%s, ", tmp->nom);
		tmp = tmp->suiv;
	}
	printf("\n");
}

