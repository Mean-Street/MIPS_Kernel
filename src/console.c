#include <inttypes.h>
#include <console.h>
#include <cpu.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>

#define MEMORY_BEGIN 0xB8000
#define NB_LIG 25
#define NB_COL 80

#define CURSOR_PORT 0x3D4
#define DATA_PORT 0x3D5
#define LOW 0x0F
#define HIGH 0x0E


uint32_t nb_IT = 0;
uint32_t nb_sec = 0;
uint32_t nb_min = 0;
uint32_t nb_heu = 0;


uint16_t *ptr_mem(uint32_t lig, uint32_t col)
	// Renvoit un pointeur sur la case mémoire correspondant aux coordonnées
{
	return (uint16_t*)(MEMORY_BEGIN + 2*(NB_COL*lig + col));
}


void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t colors)
	// Ecrit le caractère c aux coordonnées spécifiées
{
	uint16_t *addr = ptr_mem(lig, col);
	*addr = ((uint16_t)colors << 8) + c;
}


void efface_ligne(uint32_t lig)
	// Efface la ligne lig de l'écran
{
	for (uint32_t col = 0; col < NB_COL; col++) {
		ecrit_car(lig, col, ' ', 0x0F);
	}
}

void efface_ecran(void)
	// Ecrit dans chaque case un espace en blanc sur fond noir
{
	for (uint32_t lig = 0; lig < NB_LIG; lig++) {
		efface_ligne(lig);
	}
}


void place_curseur(uint32_t lig, uint32_t col)
	// Place le curseur à la position donnée
{
	uint16_t pos = col + NB_COL*lig;
	// poids faibles
	outb(LOW, CURSOR_PORT);
	outb((uint8_t)pos, DATA_PORT);
	// poids forts
	outb(HIGH, CURSOR_PORT);
	outb((uint8_t)(pos >> 8), DATA_PORT);
}


void recup_curseur(pos_curseur* curseur)
	// Charge dans curseur la position courante
{
	outb(HIGH, CURSOR_PORT);
	uint16_t pos = inb(DATA_PORT);
	pos = pos << 8;
	outb(LOW, CURSOR_PORT);
	pos = pos + inb(DATA_PORT);
	curseur->lig = pos/NB_COL;	
	curseur->col = pos % NB_COL;
}


void defilement(void)
	// Fait remonter d'une ligne l'affichage de l'écran
{
	void* deuxieme_ligne = ptr_mem(1, 0);
	size_t taille = NB_COL * (NB_LIG-1) * 2;
	memmove((void*)MEMORY_BEGIN, deuxieme_ligne, taille);
	efface_ligne(NB_LIG - 1);
}


void traite_car(char c, uint8_t colors)
	// Traite le caractère donné
	// Met à jour la position du curseur
{
	pos_curseur curseur;
	recup_curseur(&curseur);

	/* si c est un caractère spécial */
	if (c<32 || c == 127) {
		switch (c) {
			case '\b':
				if (curseur.col != 0)
					curseur.col --;
				break;
			case '\t':
				break;
				curseur.col = curseur.col + 8 - (curseur.col % 8);
				if (curseur.col == 80)
					curseur.col = 79;
				break;
			case '\n':
				curseur.lig ++;
				curseur.col = 0;
				break;
			case '\f':
				efface_ecran();
				curseur.lig = 0;
				curseur.col = 0;
				break;
			case '\r':
				curseur.col = 0;
				break;
			default:
				break;
		}
	/* si c n'est pas un caractère spécial */
	} else {
		ecrit_car(curseur.lig, curseur.col, c, colors);
		curseur.col ++;
	}

	/* mise à jour de la position du curseur */
	if (curseur.col == NB_COL) {
		curseur.col = 0;
		curseur.lig ++;
	}
	if (curseur.lig == NB_LIG) {
		defilement();
		curseur.lig --;
	}

	place_curseur(curseur.lig, curseur.col);
}



void ecrit_temps(const char* s)
{
	size_t len = strlen(s);
	if (len > NB_COL)
		len = NB_COL;

	uint32_t col = NB_COL - 1;
	for (int32_t i = len-1; i >= 0; i--) {
		ecrit_car(0, col, s[i], 0x0F);
		col--;
	}
}


void tic_PIT(void)
{
	// liberation du controleur d'interruption
	outb(0x20, 0x20);

	// gestion de l'interruption
	nb_IT++;
	if (nb_IT == CLOCKFREQ) {
		nb_IT = 0;
		nb_sec++;
		if (nb_sec == 60) {
			nb_sec = 0;
			nb_min++;
			if (nb_min == 60) {
				nb_min = 0;
				nb_heu++;
			}
		}
	}

	// calcul de l'affichage
	char s[9];
	sprintf(&(s[0]), "%02d", nb_heu);
	s[2] = ':';
	sprintf(&(s[3]), "%02d", nb_min);
	s[5] = ':';
	sprintf(&(s[6]), "%02d", nb_sec);
	ecrit_temps(s);
}


extern void console_putbytes(const char *s, int len)
{
	for (uint32_t i = 0; i < len; i++) {
		traite_car(s[i], 0x0F);
	}
}
