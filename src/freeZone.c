#include "ft_malloc.h"
#include "libft.h"

void	secuMunmap(void *ptr, size_t size) {
	debug_hex("[*] munmap( ptr=", ptr, "");
	debug_var(", size=", size, " )\n");
	g_zone.pageAlloc -= size / g_zone.pageSize;
	munmap(ptr, size);
}

int		checkBlock(void *data) {
	t_zone	*zone;
	t_block	*block;
	size_t	size;

	for (unsigned int index = 0; index < g_zone.size; index++) {
		zone = g_zone.zones[index];
		if (zone && (void*)zone + sizeof(t_zone) < (void*)data &&
			(void*)data <(void*)zone + sizeof(t_zone) + zone->size) {
			block = (void*)zone + sizeof(t_zone);
			size = zone->size;
			while (size) {
				if ((void*)block + sizeof(t_block) == data) return 1;
				size -= sizeof(t_block) + block->size;
				block = getNextBlock(block);
			}
		}
	}
	return 0;
}

void	freeZone() {
	int counterTypeZone[4];
	t_zone	*zone;

	counterTypeZone[0] = 0;
	counterTypeZone[1] = 0;
	counterTypeZone[2] = 0;
	counterTypeZone[3] = 0;
	for (unsigned int index = 0; index < g_zone.size; index++) {
		zone = g_zone.zones[index];
		if (zone) {
			counterTypeZone[zone->type]++;
			if (counterTypeZone[zone->type] > 1
				&& getFirstBlock(zone)->free && getFirstBlock(zone)->size + sizeof(t_block) == zone->size) {
				debug_var("[*] Free zone index=", index, "\n");
				secuMunmap(zone, zone->size + sizeof(t_zone));
				g_zone.zones[index] = NULL;
			}
		}
	}
}

void	removeBlock(t_block *block) {
	t_block *next;
	t_block *prev;

	block->free = 1;
	debug_var("[*] removeBlock( ", block->size, " )\n");
	if (!isLastBlock(block)) {
		next = getNextBlock(block);
		if (next->free)	{
			block->size += sizeof(t_block) + next->size;
			ft_bzero(next, sizeof(t_block));
		}
	}
	if ((prev = getPrevBlock(block))) {
		if (prev->free) {
			prev->size += sizeof(t_block) + block->size;
			ft_bzero(block, sizeof(t_block));
		}
	}
}