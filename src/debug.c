#include "ft_malloc.h"
#include "libft.h"
#include <stdint.h>

extern t_zones g_zone;

void ft_puthex(unsigned long long int hex, int min) {
	char	str[23];
	char	strHex[] = "0123456789ABCDEF";
	int		index = 23;

	memset(str, '0', 23);
	while (hex) {
		index--;
		str[index] = strHex[hex % 16];
		hex /= 16;
	}
	if (23 - index > min) {
		write(1, &str[index], 23 - index);
	} else {
		write(1, &str[23 - min], min);
	}
}

void showBlocks(t_block *block, unsigned int sizeZone) {
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

void showBlocksHex(t_block *block, unsigned int sizeZone) {
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
				ft_puthex(data[index], 2);
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

void initDebug() {
	char *env;

	if (!g_zone.debug) {
		env = getenv("DEBUG_MALLOC");	
		if (!ft_strcmp(env, "0")) {
			g_zone.debug = desactivate;
		} else if (!ft_strcmp(env, "1")) {
			g_zone.debug = activate;
		}
	}
}

void debug_str(char *str) {
	initDebug();

	if (g_zone.debug == activate) {
		ft_putstr(str);
	}
}

void	debug_var(char *name, long long int var, char *end) {
	initDebug();

	if (g_zone.debug == activate) {
		ft_putstr(name);
		ft_putnbr(var);
		ft_putstr(end);
	}
}

void	debug_hex(char *name, void *var, char *end) {
	initDebug();

	if (g_zone.debug == activate) {
		ft_putstr(name);
		ft_putstr("0x");
		ft_puthex((uintptr_t)var, 8);
		ft_putstr(end);
	}
}

void	ft_putvarint(char *name, long long int var) {
	ft_putstr(name);
	ft_putstr(" = ");
	ft_putnbr(var);
	ft_putchar('\n');
}