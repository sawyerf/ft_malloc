#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zone;

void showBlocks(t_block *block, int sizeZone) {
	int sizeBlock;

	if (sizeZone <= 0) {
		return (NULL);
	}
	ft_putchar('#');
	ft_putnbr(block->size);
	if (!block->free) {
		ft_putstr("***");
	} else {
		ft_putstr("...");
	}
	sizeBlock = sizeof(t_block) + block->size;
	return showBlocks(block + sizeBlock, sizeZone - sizeBlock);
}

void show_alloc_mem(void) {
	for (unsigned int index = 0; index < g_zones.size; index++) {
		if (g_zones.zones[i]) {
			showBlocks(
				g_zones.zones[i]->zone + sizeof(t_zone),
				size,
			);
		}
	}
}