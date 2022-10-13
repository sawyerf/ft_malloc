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

t_block		*getPrevBlock(t_block *block) {
	t_block	*prev;
	t_block *next;
	
	next = NULL;
	prev = getFirstBlock(g_zone.zones[block->indexZone]);
	while (block != prev) {
		next = getNextBlock(prev);
		if (next == block) return (prev);
		prev = next;
	}
	return (NULL);
}

int	isLastBlock(t_block *block) {
	t_zone *zone;

	zone = g_zone.zones[block->indexZone];
	if ((void*)getFirstBlock(zone) + zone->size == getNextBlock(block)) {
		return 1;
	} else {
		return 0;
	}
}

int	getSizeZone(size_t size) {
	if (size <= MAX_SIZE_TINY) {
		return (tiny);
	} else if (size <= MAX_SIZE_SMALL) {
		return (small);
	} else {
		return (large);
	}
}