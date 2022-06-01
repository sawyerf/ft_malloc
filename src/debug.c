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

void light_show_zone(void *zone) {
	t_block *block;

	block = zone;
	if (!block) {
		ft_printf("\n");
		return ;
	}
	ft_printf("#%ld", block->size);
	if (!block->free) {
		ft_printf("***");
	} else {
		ft_printf("...");
	}
	return light_show_zone(block->next);
}