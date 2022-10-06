#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "ft_malloc.h"

int main() {
	int size = 400;
	void *tab[size];
	void *tabCalloc[size];
	int randomSize[] = {24, 552, 1024, 5000};
	void *ptr;

	printf("t_block: %ld\n", sizeof(t_block));
	ptr = ft_malloc(1);
	for (int index = 0; index < size; index++) {
		if ((tab[index] = ft_malloc(randomSize[index % 4]))) {
			memset(tab[index], 0, randomSize[index % 4]);
			memcpy(tab[index], "desbarres", 10);
		} else {
			printf("ca renvoie NULL\n");
		}
		tab[index] = ft_realloc(tab[index], randomSize[index % 4] + index % 50);
		memset(tab[index], 0, randomSize[index % 4] + index % 50);
		memcpy(tab[index], "PARIS ! PARIS !", 15);
		if (!(index % 3)) {
			ft_free(tab[index]);
			tab[index] = NULL;
		}
	}
	// show_alloc_mem_ex();

	for (int index = 0; index < size; index++) {
		if ((tabCalloc[index] = ft_calloc(randomSize[index % 4], sizeof(char)))) {
			memset(tabCalloc[index], 0, randomSize[index % 4] * sizeof(char));
			memcpy(tabCalloc[index], "desbarres", 10);
		} else {
			printf("ca renvoie NULL\n");
		}
		tabCalloc[index] = ft_reallocarray(tabCalloc[index], randomSize[index % 4] + index % 50, sizeof(char));
		memset(tabCalloc[index], 0, (randomSize[index % 4] + index % 50) * sizeof(char));
		memcpy(tabCalloc[index], "PARIS ! PARIS !", 15);
		if (!(index % 3)) {
			ft_free(tabCalloc[index]);
			tabCalloc[index] = NULL;
		}
	}

	for (int index = 0; index < size; index++) {
		ft_free(tab[index]);
		ft_free(tabCalloc[index]);
	}
	ft_free(ptr);
	// show_alloc_mem_ex();
}
