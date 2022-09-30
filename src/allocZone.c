#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zone;

void	init_block(void *zone, size_t size, unsigned int ori)
{
	t_block *block;

	block = zone;
	block->size = size;
	block->free = 1;
	block->zone = ori;
}

void	*secuMunmap(size_t size) {
	return mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0)
}

// set variable of new allcate block
void	set_block(t_block *block, size_t size) {
	t_block *next;

	block->free = 0;
	next = NULL;
	if (block->size - size >= sizeof(t_block)) {
		next = block + sizeof(t_block) + size;
		init_block((void*)next, block->size - size - sizeof(t_block), block->zone);
		block->size = size;
	}
}

void	*alloc_zone(size_t size_block) {
	void	*zone;
	size_t	real_size;
	size_t	real_size_block;
	size_t	page_size;
	
	page_size = getpagesize();
	real_size_block = (size_block + sizeof(t_block));
	if (size_block <= MAX_SIZE_MEDIUM) {
		real_size_block *= 100 ;
	}
	real_size = (real_size_block / page_size + 1) * page_size;
	zone = secuMunmap(real_size);
	init_block(zone, real_size - sizeof(t_block), 0);
	return (zone);
}

t_block	*last_block(void *zone) {
	t_block *block;

	block = zone;
	while (block && block->next) {
		block = block->next;
	}
	return block;
}

void	*add_zone(void *zone, size_t size_block) {
	t_block	*new;

	if (!(new = alloc_zone(size_block))) return (zone);
	new->prev = last_block(zone);
	if (!new->prev) return new;
	new->zone = (new->prev)->zone + 1;
	(new->prev)->next = new;
	return zone;
}

void	allocTabZones() {
	size_t	pageSize = getpagesize();
	t_zone	**newZones;

	newZones = secuMunmap((g_zones.numPage + 1) * pageSize);
	if (g_zones.zones) {
		ft_memcpy(newZones, g_zones.zones, g_zones.numPage * pageSize);
		munmap(g_zones.zones, g_zones.numPage * pageSize);
		ft_memset(*newZones + g_zones.numPage * pageSize, 0, pageSize);
	}
	g_zones.numPage++;
	g_zones.size = (g_zones.numPage * pageSize) / sizeof(*t_zone);
	g_zones.zones = newZones;
}

void	*find_freeblock(size_t size, int typeZone) {
	void *free_block;

	if (g_zones.zones) {
		allocTabZones();
	}
	free_block = findBlock(size, typeZone);
	if (free_block) {
		return free_block;
	} else {
		add_zone(zone, size_block);
		return findBlock(size, typeZone);
	}
}

t_block	*findFreeBlock(t_block *block, size_t size, size_t sizeZone) {
	if (sizeZone <= 0) {
		return (NULL);
	}
	if (block->free && block->size <= size) {
		return (block);
	}
	return findFreeBlock(block + sizeof(t_block) + block->size, size, sizeZone - sizeof(t_block) - block->size);
}

void	*findBlock(size_t size, int typeZone) {
	t_block	*block;

	for (unsigned int index = 0; index < g_zones.size; index++) {
		if (g_zones.zones[i] && g_zones.zones[i]->type == typeZone) {
			block = findFreeBlock(
				g_zones.zones[i]->zone + sizeof(t_zone),
				size,
				g_zones.zones[i]->size
			);
		}
	}
}