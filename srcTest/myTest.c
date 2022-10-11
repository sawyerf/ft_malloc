#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "ft_malloc.h"

int main() {
	int size = 500;
	void *tab[size];
	void *tabCalloc[size];
	int randomSize[] = {24, 552, 1024, 5000};
	void *ptr;

	ptr = malloc(1);
	for (int index = 0; index < size; index++) {
		if ((tab[index] = malloc(randomSize[index % 4]))) {
			memset(tab[index], 10, randomSize[index % 4]);
			// memcpy(tab[index], "desbarres", 10);
		} else {
			printf("ca renvoie NULL\n");
		}
		tab[index] = realloc(tab[index], randomSize[index % 4] + index % 50);
		memset(tab[index], 10, randomSize[index % 4] + index % 50);
		// memcpy(tab[index], "PARIS ! PARIS !", 15);
		if (!(index % 2)) {
			free(tab[index]);
			tab[index] = NULL;
		}
	}
	// show_alloc_mem_ex();

	for (int index = 0; index < size; index++) {
		if ((tabCalloc[index] = calloc(randomSize[index % 4], sizeof(char)))) {
			memset(tabCalloc[index], 10, randomSize[index % 4] * sizeof(char));
			memcpy(tabCalloc[index], "desbarres", 10);
		} else {
			printf("ca renvoie NULL\n");
		}
		tabCalloc[index] = reallocarray(tabCalloc[index], randomSize[index % 4] + index % 50, sizeof(char));
		memset(tabCalloc[index], 10, (randomSize[index % 4] + index % 50) * sizeof(char));
		// memcpy(tabCalloc[index], "PARIS ! PARIS !", 15);
		if (!(index % 2)) {
			free(tabCalloc[index]);
			tabCalloc[index] = NULL;
		}
	}

	for (int index = 0; index < size; index++) {
		// if (!(index == 4 || index == 3 || index == 5)) {
		free(tab[index]);
		free(tabCalloc[index]);
		// }
	}
	free(ptr);
	// show_alloc_mem_ex();
}
