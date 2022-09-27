#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zones;

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

void show_alloc_mem(void) {
	ft_putstr("======================\n");
	ft_putstr("# TINY\n");
	light_show_zone(g_zones.tiny);
	ft_putstr("# SMALL\n");
	light_show_zone(g_zones.medium);
	ft_putstr("# LARGE\n");
	light_show_zone(g_zones.large);
	ft_putstr("======================\n");
}