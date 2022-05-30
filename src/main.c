#include <stdio.h>
#include <unistd.h>
#include "ft_malloc.h"

extern t_zones g_zones;

int main() {
	// printf("%d\n", getpagesize());
	printf("t_block: %ld\n", sizeof(t_block));
	for (int index = 0; index < 100; index++) {
		if (!ft_malloc(MAX_SIZE_TINY)) {
			ft_printf("fin: %d", index);
			return (0);
		}
	}
	show_zone(g_zones.tiny);
}