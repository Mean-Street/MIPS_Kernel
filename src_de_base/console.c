#include <inttypes.h>
#include <console.h>
#include <cpu.h>

#define MEMORY_BEGIN 0xB8000
#define NB_LIG 25
#define NB_COL 80

#define CURSOR_PORT 0x3D4
#define DATA_PORT 0x3D5
#define LOW 0x0F
#define HIGH 0x0E

uint16_t *ptr_mem(uint32_t lig, uint32_t col)
	// Renvoit un pointeur sur la case mémoire correspondant aux coordonnées fournies
{
	return (uint16_t*)(MEMORY_BEGIN + 2*(NB_COL*lig + col));
}


void ecrit_car(uint32_t lig, uint32_t col, char c, uint8_t colors)
	// Ecrit le caractère c aux coordonnées spécifiées
{
	uint16_t *addr = ptr_mem(lig, col);
	*addr = ((uint16_t)colors << 8) + c;
}


void efface_ecran(void)
	// Ecrit dans chaque case un espace en blanc sur fond noir
{
	for (uint32_t lig = 0; lig < NB_LIG; lig++) {
		for (uint32_t col = 0; col < NB_COL; col++) {
			ecrit_car(lig, col, ' ', 0x0F);
		}
	}
}


void place_curseur(uint32_t lig, uint32_t col)
	// Place le curseur à la position donnée
{
	uint16_t pos = col +NB_COL*lig;
	// poids faibles
	outb(LOW, CURSOR_PORT);
	outb((uint8_t)pos, DATA_PORT);
	// poids forts
	outb(HIGH, CURSOR_PORT);
	outb((uint8_t)(pos >> 8), DATA_PORT);
}


pos_curseur recup_curseur(void)
{
	pos_curseur *cursor = malloc(sizeof(pos_curseur));
	outb(HIGH, CURSOR_PORT);
	uint16_t pos = inb(DATA_PORT);
	pos = pos << 8;
	outb(LOW, CURSOR_PORT);
	pos = pos + inb(DATA_PORT);
	cursor->lig = pos/NB_COL;	
	cursor->col = pos % NB_COL;
	return cursor;
}


void traite_car(char c, uint8_t colors)
	// Traite le caractère donné
{
	pos_curseur *cursor = recup_curseur();

	if (c<32 || c == 127) {
		switch (c) {
			case '\b':
				if (cursor->col != 0)
					place_cursor(cursor->lig, cursor->lig-1);
				break;
			case '\t':
				uint32_t col = cursor->col + 8 - (cursor->col % 8);
				if col == 80:
					col = 79;
				place_cursor(cursor->lig, col);
				break;
			case '\n':
				// TODO
				break;
			case '\f':
				// TODO
				break;
			case '\r':
				// TODO
				break;
			default:
				// TODO
				break;
		}
	} else {
		ecrit_car(cursor->lig, cursor->col, c, colors);
		if (cursor->col = NB_COL-1) {
			place_curseur(cursor->lig+1, 0);
		} else {
			place_curseur(cursol->lig, cursor->col+1);
		}
		}
		}
	}
}


void defilement(void)
	// Fait remonter d'une ligne l'affichage de l'écran
{
	return;
}


extern void console_putbytes(const char *s, int len)
{
	/* efface_ecran(); */
	uint32_t lig = 0;
	uint32_t col = 0;
	for (uint32_t i = 0; i < len; i++) {
		traite_car(lig, col, s[i], 0x0F);
		col++;
		if (col == NB_COL) {
			col = 0;
			lig++;
		}
	}
}
