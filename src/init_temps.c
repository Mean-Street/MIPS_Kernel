#include <console.h>
#include <segment.h>
#include <cpu.h>
#include <stdbool.h>

#define table_IT 0x1000
#define QUARTZ 0x1234DD
#define CLOCKPORT 0x40

void init_traitant_IT(int32_t num_IT, void (*traitant)(void))
{
	uint32_t* addr = (uint32_t*)table_IT + 2*num_IT;

	*addr = ((uint32_t)KERNEL_CS) << 16 | ((uint32_t)traitant & 0x0000FFFF);
	*(addr + 1) = ((uint32_t)traitant & 0xFFFF0000) | 0x00008E00;
}


void init_horloge(void)
{
	outb(0x34, 0x43);
	outb((QUARTZ / CLOCKFREQ) % 256, CLOCKPORT); // poids faibles
	outb((QUARTZ / CLOCKFREQ) >> 8, CLOCKPORT); // poids forts
}


void masque_IRQ(uint32_t num_IRQ, bool masque)
{
	uint8_t a = inb(0x21);
	uint8_t m = 0x01 << num_IRQ;
	if (masque == 1) {
		a = a | m;
	} else {
		a = a | (~m);
	}
	outb(0xFE, 0x21);
}
