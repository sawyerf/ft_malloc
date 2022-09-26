#include "ft_malloc.h"
#include "libft.h"

void show_zone(void *zone) {
	t_block *block;

	block = zone;
	if (!block) {
		ft_putstr("\n");
		return ;
	}
	// for (size_t size = sizeof(t_block); size; size--) {
	ft_putchar('#');
	ft_putnbr(block->size);
	// }
	for (size_t size = block->size; size; size--) {
		if (!block->free) {
			ft_putstr("*");
		} else {
			ft_putstr(".");
		}
	}
	return show_zone(block->next);
}

void light_show_zone(void *zone) {
	t_block *block;

	block = zone;
	if (!block) {
		ft_putstr("\n");
		return ;
	}
	// if (!block->prev || ((block->prev)->zone != block->zone)) printf("\n%p:\n", block->zone);
	ft_putchar('#');
	ft_putnbr(block->size);
	if (!block->free) {
		ft_putstr("***");
	} else {
		ft_putstr("...");
	}
	return light_show_zone(block->next);
}
