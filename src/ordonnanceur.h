#ifndef ORDONNANCEUR_H
#define ORDONNANCEUR_H

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <proc_list.h>
#include <string.h>
#include <cpu.h>
#include <console.h>

#define TAILLE_PILE 512
#define NB_PROC_MAX 8


list_activable* init_list(void);

void clear_mourant(list_mourant* l);

void init_idle(char* nom);

int32_t cree_processus(void (*code)(void), char* nom);

void fin_processus(void);

void ordonnance(void);

void ctx_sw(int32_t* old_reg, int32_t* new_reg);

void idle(void);

uint32_t nbr_secondes(void);

void proc1(void);
void proc2(void);
void proc3(void);

#endif
