#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

void    initZone(t_zone *zone, t_type_zone typeZone, size_t size) {
    zone->type = typeZone;
	zone->size = size;
}

void	initBlock(void *zone, size_t size, unsigned int indexZone)
{
	t_block *block;

	block = zone;
	block->size = size;
	block->free = 1;
	block->indexZone = indexZone;
}

t_block     *getFirstBlock(void *zone) {
    return zone + sizeof(t_zone);
}

t_block     *getNextBlock(t_block *block) {
    return ((void*)block + sizeof(t_block) + block->size);
}