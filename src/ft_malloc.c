#include <unistd.h>
#include <stdio.h>
#include "ft_malloc.h"

void	*ft_malloc(size_t size) {
	(void)size;
	if (!size) return (NULL);
	return alloc_zone(MAX_SIZE_TINY);
}