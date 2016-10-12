#ifndef __INIT_TEMPS_H__
#define __INIT_TEMPS_H__

#include <inttypes.h>
#include <stdbool.h>

void init_traitant_IT(int32_t num_IT, void (*traitant)(void));

void init_horloge(void);

void masque_IRQ(uint32_t num_IRQ, bool masque);

void traitant_IT_32(void);

#endif
