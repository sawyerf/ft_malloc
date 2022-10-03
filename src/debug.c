#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zone;

void	ft_putvarint(char *name, long long int var) {
	ft_putstr(name);
	ft_putstr(" = ");
	ft_putnbr(var);
	ft_putchar('\n');
}

void showBlocks(t_block *block, unsigned int sizeZone) {
	int sizeBlock;

	if (sizeZone <= 0) {
		return ;
	}
	ft_putchar('#');
	ft_putnbr(block->size);
	if (!block->free) {
		ft_putstr("***");
	} else {
		ft_putstr("...");
	}
	sizeBlock = sizeof(t_block) + block->size;
	return showBlocks((void*)block + sizeBlock, sizeZone - sizeBlock);
}

void show_alloc_mem(void) {
	for (unsigned int index = 0; index < g_zone.size; index++) {
		if (g_zone.zones[index]) {
			ft_putstr("\n#=== Tab index = ");
			ft_putnbr(index);
			ft_putstr(", type = ");
			ft_putnbr(g_zone.zones[index]->type);
			ft_putstr(", size = ");
			ft_putnbr(g_zone.zones[index]->size);
			ft_putstr(" ===#\n");
			showBlocks(
				(t_block*)((void*)g_zone.zones[index] + sizeof(t_zone)),
				g_zone.zones[index]->size
			);
		}
	}
	ft_putstr("\n\n");
}