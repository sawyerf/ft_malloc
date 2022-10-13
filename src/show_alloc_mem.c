#include "ft_malloc.h"
#include "libft.h"

static void showBlocks(t_block *block, unsigned int sizeZone) {
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
	return showBlocks(getNextBlock(block), sizeZone - (sizeof(t_block) + block->size));
}

static void showBlocksHex(t_block *block, size_t sizeZone) {
	char	*data;
	int		isZero = 0;

	if (sizeZone <= 0) {
		return ;
	}
	ft_putstr("| ");
	ft_putnbr(block->size);
	ft_putstr(" | ");
	ft_putnbr(block->free);
	ft_putstr("    | ");
	ft_putnbr(block->indexZone);
	ft_putstr("         | ");
	data = (void*)block + sizeof(t_block);
	if (!block->free) {
		for (size_t index = 0; block->size > index; index++) {
			if (!isZero && !data[index]) {
				ft_putstr(" 00...");
				isZero = 1;
			} else if (data[index]) {
				isZero = 0;
				ft_putchar(' ');
				puthex(data[index], 2);
			}
		}
	} else {
		ft_putstr(" ...");
	}
	ft_putstr("\n");
	return showBlocksHex(getNextBlock(block), sizeZone - (sizeof(t_block) + block->size));
}

void show_alloc_mem_ex(void) {
	for (unsigned int index = 0; index < g_zone.size; index++) {
		if (g_zone.zones[index]) {
			ft_putstr("\n#=== Tab index = ");
			ft_putnbr(index);
			ft_putstr(", type = ");
			ft_putnbr(g_zone.zones[index]->type);
			ft_putstr(", size = ");
			ft_putnbr(g_zone.zones[index]->size);
			ft_putstr(" ===#\n");
			ft_putstr("| Size | Free | IndexZone | Data |\n");
			showBlocksHex(
				getFirstBlock(g_zone.zones[index]),
				g_zone.zones[index]->size
			);
		}
	}
	ft_putstr("\n\n");
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
				getFirstBlock(g_zone.zones[index]),
				g_zone.zones[index]->size
			);
		}
	}
	ft_putstr("\n\n");
}