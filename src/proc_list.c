#include <proc_list.h>

/* Liste des activables */
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


void disp_list_activable(list_activable* l)
{
	processus* tmp = l->tete;
	printf("Activable, len = %d\n", l->len);
	while (tmp != NULL) {
		printf("%s, ", tmp->nom);
		tmp = tmp->suiv;
	}
	printf("\n");
}


/* Liste des endormis */
void add_elt(list_endormi* l, processus* proc, uint32_t temps_reveil)
{
	proc->temps_reveil = temps_reveil;
	proc->etat_courant = ENDORMI;
	if (l->len == 0) {
		l->tete = proc;
		proc->suiv = NULL;
	} else {
		processus* curr = NULL;
		processus* next = l->tete;
		while (next != NULL && temps_reveil > next->temps_reveil) {
			curr = next;
			next = next->suiv;
		}
		if (curr == NULL) {
			l->tete = proc;
		} else {
			curr->suiv = proc;
		}
		proc->suiv = next;
	}

	l->len++;
}

bool is_empty(list_endormi* l)
{
	return (l->tete == NULL);
}

uint32_t get_prio(list_endormi* l)
{
	if (l->tete == NULL) {
		return 0;
	}
	return l->tete->temps_reveil;
}

processus* pop_prio(list_endormi* l)
{
	if (l->tete == NULL) {
		return NULL;
	}
	processus* tmp = l->tete;
	l->tete = l->tete->suiv;
	l->len--;
	tmp->etat_courant = ACTIVABLE;
	return tmp;
}

void disp_list_endormi(list_endormi* l)
{
	processus* tmp = l->tete;
	printf("Endormi, len = %d\n", l->len);
	while (tmp != NULL) {
		printf("%s[%d], ", tmp->nom, tmp->temps_reveil);
		tmp = tmp->suiv;
	}
	printf("\n");
}
