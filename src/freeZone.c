#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zone;

void	freeZone(t_zone *zone) {
	munmap(*block, (*block)->size + sizeof(t_block));
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

	block = zone;
	block->free = 1;
	prev = block->prev;
	if (prev && prev->free == 1 && prev->zone == block->zone) {
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
			return del_block(block->next);
		}
	}
}
