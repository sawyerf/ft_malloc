#include <sys/mman.h>
#include <stdio.h>
#include "ft_malloc.h"

void	init_block(void *zone, size_t size)
{
	t_block *block;

	block = zone;
	// block->size_prev = 0;
	block->size = size;
	block->next = NULL;
	block->prev = NULL;
	block->free = 1;
}

void	set_block(void *zone, size_t size)
{
	t_block *block;
	t_block *next;

	block = zone;
	block->free = 0;
	next = NULL;
	if (block->size - size >= sizeof(t_block)) {
		next = zone + sizeof(t_block) + size;
		init_block((void*)next, block->size - size - sizeof(t_block));
		next->prev = block;
		// next->size_prev = size;
	}
	block->next = next;
	block->size = size;
}

void	del_block(void *zone) {
	t_block *block;
	t_block *next;

	block = zone;
	next = block->next;
	if (next && next->free == 1) {
		del_block((void*)block->next);
		block->size += next->size;
		block->next = next->next;
	}
	// delete before
	block->free = 1;
}

void	*find_block(void *zone, size_t size) {
	t_block *block;
	t_block *prop;

	block = zone;
	if (!block ) {
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

void	*alloc_zone(size_t size_block) {
	void	*zone;
	size_t	real_size;
	size_t	real_size_block;
	size_t	page_size;
	
	page_size = getpagesize();
	real_size_block = (size_block + sizeof(t_block)) * 100;
	real_size = real_size_block + page_size - (real_size_block % page_size); // t_block est gros
	zone = mmap(NULL, real_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS|MAP_PRIVATE, -1, 0);
	printf("barres: %ld\n", real_size);
	init_block(zone, real_size - sizeof(t_block));
	// show_zone(zone);
	return (zone);
}