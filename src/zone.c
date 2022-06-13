#include <sys/mman.h>
#include <stdio.h>
#include "ft_malloc.h"

extern t_zones g_zones;

void	init_block(void *zone, size_t size, void *ori)
{
	t_block *block;

	block = zone;
	// block->size_prev = 0;
	block->size = size;
	block->next = NULL;
	block->prev = NULL;
	block->free = 1;
	block->zone = ori;
}

void	set_block(void *zone, size_t size) {
	t_block *block;
	t_block *next;

	block = zone;
	block->free = 0;
	next = NULL;
	if (block->size - size >= sizeof(t_block)) {
		next = zone + sizeof(t_block) + size;
		init_block((void*)next, block->size - size - sizeof(t_block), block->zone);
		next->prev = block;
		next->next = block->next;
		// next->size_prev = size;
	}
	block->next = next;
	block->size = size;
}

	// ft_printf("next: %p\n", block->next);
	// ft_printf("prev: %p\n", block->prev);
	// ft_printf("prev: %p\n", (block->next)->prev);
	// ft_printf("size: %d\n", block->size);
	// ft_printf("next: %p\n", );

void	freeZone(t_block **block) {
	ft_printf("free: zone %p\n", (*block)->zone);
	munmap((*block)->zone, (*block)->size + sizeof(t_block));
	*block = NULL;
}

void	free_block(t_block *block) {
	t_block *prev;
	t_block *next;

	prev = block->prev;
	next = block->next;

	if (prev) {
		prev->next = next;
	}
	if (next) {
		next->prev = prev;
	}
	freeZone(&block);
}

void	del_block(void *zone) {
	t_block *block;
	t_block *next;
	t_block *prev;

	// light_show_zone(g_zones.tiny);
	block = zone;
	block->free = 1;
	prev = block->prev;
	if (prev && prev->free == 1 && prev->zone == block->zone) {
		// ft_printf("prev <--\n");
		return del_block(prev);
	}
	next = block->next;
	if (next && next->free == 1 && next->zone == block->zone) {
		block->size += next->size + sizeof(t_block);
		block->next = next->next;
		if (next->next) {
			(next->next)->prev = block;
		}
		if (block->prev &&
			(block->prev)->zone != block->zone &&
			((block->next && (block->next)->zone != block->zone) || !block->next)) {
			return free_block(block);
		}
		if (block && block->next && (block->next)->free == 1) {
		// ft_printf("next -->\n");
			return del_block(block->next);
		}
	}
}

void	*alloc_zone(size_t size_block) {
	void	*zone;
	size_t	real_size;
	size_t	real_size_block;
	size_t	page_size;
	
	page_size = getpagesize();
	real_size_block = (size_block + sizeof(t_block)) * 100;
	real_size = real_size_block + page_size - (real_size_block % page_size); // t_block est gros
	zone = mmap(NULL, real_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	ft_printf("barres: %p\n", zone);
	init_block(zone, real_size - sizeof(t_block), zone);
	// show_zone(zone);
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
	(new->prev)->next = new;
	// light_show_zone(zone);	
	return zone;
}

void	*find_freeblock(void *zone, size_t size, size_t size_block) {
	void *free_block;
	
	free_block = find_block(zone, size);
	if (free_block) {
		return free_block;
	} else {
		add_zone(zone, size_block);
		return find_block(zone, size);
	}
}

void	*find_block(void *zone, size_t size) {
	t_block *block;
	t_block *prop;

	block = zone;
	if (!block) {
		return (block);
	}
	prop = find_block(block->next, size);
	if (!block->free) return (prop);
	if (block->size == size) return (block);
	if (prop && (prop->size == size || prop->size < block->size)) {
		return (prop);
	}
	if (block->next && block->size >= size + sizeof(t_block)) {
		return (block);
	}
	if (!block->next && block->size >= size) {
		return (block);
	}
	return (prop);
}