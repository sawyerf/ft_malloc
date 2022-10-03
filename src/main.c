#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ft_malloc.h"

int main() {
	int size = 400;
	void *tab[size];
	void *ptr;

	printf("t_block: %ld\n", sizeof(t_block));
	ptr = ft_malloc(1);
	for (int index = 0; index < size; index++) {
		if ((tab[index] = ft_malloc(2000))) {
			memcpy(tab[index], "desbarres", 10);
		} else {
			printf("ca renvoie NULL\n");
		}
	}
	show_alloc_mem();

	for (int index = 0; index < size; index++) {
		// if (!(index == 4 || index == 3 || index == 5)) {
			ft_free(tab[index]);
		// }
	}
	ft_free(ptr);
	show_alloc_mem();
}
