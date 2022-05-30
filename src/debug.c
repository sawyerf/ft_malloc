#include "ft_malloc.h"

void show_zone(void *zone) {
	t_block *block;

	block = zone;
	if (!block) {
		ft_printf("\n");
		return ;
	}
	// for (size_t size = sizeof(t_block); size; size--) {
	ft_printf("#%ld", block->size);
	// }
	for (size_t size = block->size; size; size--) {
		if (!block->free) {
			ft_printf("*");
		} else {
			ft_printf(".");
		}
	}
	return show_zone(block->next);
}