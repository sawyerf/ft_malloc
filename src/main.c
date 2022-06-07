#include <stdio.h>
#include <unistd.h>
#include "ft_malloc.h"

extern t_zones g_zones;

int main() {
	int size = 400;
	void *tab[size];

	// printf("%d\n", getpagesize());
	printf("t_block: %ld\n", sizeof(t_block));
	// ft_malloc(1);
	// light_show_zone(g_zones.tiny);
	for (int index = 0; index < size; index++) {
		if (!(tab[index] = ft_malloc(MAX_SIZE_TINY))) {
			ft_printf("fin: %d\n", index);
			return (0);
		}
	}
	for (int index = 0; index < size; index++) {
		if (index == 4 || index == 3 || index == 5) {
			ft_free(tab[index]);
		}
	}
	// show_zone(g_zones.tiny);
	tab[3] = ft_malloc(3);
	tab[4] = ft_malloc(25);
	tab[5] = ft_malloc(15);
	// show_zone(g_zones.tiny);
	for (int index = 0; index < size; index++) {
		// ft_printf("%d\n", index);
		ft_free(tab[index]);
	}
	light_show_zone(g_zones.tiny);
}