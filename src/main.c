#include <stdio.h>
#include <unistd.h>
#include "ft_malloc.h"

extern t_zones g_zones;

int main() {
	int size = 400;
	void *tab[size];

	printf("t_block: %ld\n", sizeof(t_block));
	ft_malloc(1);
	printf("================= \n");
	light_show_zone(g_zones.tiny);
	for (int index = 0; index < size; index++) {
		if (!(tab[index] = ft_malloc(MAX_SIZE_TINY))) {
			memcpy(tab[index], "desbarres", 10);
		}
	}
	printf("================= \n");
	light_show_zone(g_zones.tiny);

	for (int index = 0; index < size; index++) {
		if (!(index == 4 || index == 3 || index == 5)) {
			ft_free(tab[index]);
		}
	}
	printf("================= \n");
	light_show_zone(g_zones.tiny);
	// tab[6] = ft_malloc(3);
	// tab[7] = ft_malloc(25);
	// tab[8] = ft_malloc(15);
}
