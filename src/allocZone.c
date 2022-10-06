#include <sys/mman.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/resource.h>
#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zone;

// set variable of new allcate block
void	set_block(t_block *block, size_t size) {
	block->free = 0;
	debug_var("[*] setBlock( size=", size, " )");
	debug_var(" indexZone=", block->indexZone, "\n");
	if (block->size - size >= sizeof(t_block)) {
		initBlock(
			(void*)block + sizeof(t_block) + size,
			block->size - size - sizeof(t_block),
			block->indexZone
		);
		block->size = size;
	}
}

void	*secuMmap(size_t size) {
	struct rlimit rlim;
	unsigned long long int maxPage;
	int nbPage = size / getpagesize();

	debug_var("[*] mmap( size=", size, " )");
	debug_var(" page=", nbPage, "\n");
	getrlimit(RLIMIT_DATA, &rlim);
	maxPage = rlim.rlim_cur / getpagesize();
	if (maxPage < g_zone.pageAlloc + nbPage) return (NULL);
	g_zone.pageAlloc += nbPage;
	return mmap(NULL,
		size,
		PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS|MAP_PRIVATE,
		-1,
		0
	);
}

void	*allocZone(size_t sizeBlock, t_type_zone typeZone) {
	t_zone	*zone;
	size_t	real_size;
	size_t	real_size_block;
	size_t	page_size;
	
	debug_var("[*] allocZone( sizeBlock=", sizeBlock, "");
	debug_var(", typeZone=", typeZone, " )\n");
	page_size = getpagesize();
	if (typeZone == tiny) {
		sizeBlock = MAX_SIZE_TINY;
	} else if (typeZone == small) {
		sizeBlock = MAX_SIZE_SMALL;
	}
	real_size_block = (sizeBlock + sizeof(t_block));
	if (typeZone != large) {
		real_size_block *= 100;
	}
	real_size = (real_size_block / page_size + 1) * page_size;
	if (!(zone = secuMmap(real_size))) return (NULL);
	initZone(zone, typeZone, real_size - sizeof(t_zone));
	initBlock(getFirstBlock(zone), real_size - sizeof(t_zone) - sizeof(t_block), 0);
	return (zone);
}

void	allocTabZones() {
	size_t	pageSize = getpagesize();
	t_zone	**newZones;

	debug_str("[*] Alloc Tab Zone\n");
	if (!(newZones = secuMmap((g_zone.numPage + 1) * pageSize))) return ;
	if (g_zone.zones) {
		ft_memcpy(newZones, g_zone.zones, g_zone.numPage * pageSize);
		secuMunmap(g_zone.zones, g_zone.numPage * pageSize);
		ft_memset((void*)*newZones + (g_zone.numPage * pageSize), 0, pageSize);
	}
	g_zone.numPage++;
	g_zone.size = (g_zone.numPage * pageSize) / sizeof(t_zone*);
	g_zone.zones = newZones;
}

int addZoneToTab(t_zone *zone) {
	t_block *block;

	for (unsigned int index = 0; index < g_zone.size; index++) {
		if (!g_zone.zones[index]) {
			g_zone.zones[index] = zone;
			block = getFirstBlock(zone);
			block->indexZone = index;
			return 1;
		}
	}
	return 0;
}

void	addZone(size_t size, t_type_zone typeZone) {
	t_zone	*new;

	if (!(new = allocZone(size, typeZone))) return ;
	if (!addZoneToTab(new)) {
		allocTabZones();
		addZoneToTab(new);
	}
}

t_block	*findFreeBlock(t_block *block, size_t size, size_t sizeZone) {
	if (sizeZone <= 0) {
		return (NULL);
	}
	if (block->free && block->size >= size) {
		return (block);
	}
	return findFreeBlock(
		getNextBlock(block),
		size,
		sizeZone - sizeof(t_block) - block->size);
}

void	*findBlock(size_t size, t_type_zone typeZone) {
	t_block	*block;

	for (unsigned int index = 0; index < g_zone.size; index++) {
		if (g_zone.zones[index] && g_zone.zones[index]->type == typeZone) {
			block = findFreeBlock(
				getFirstBlock(g_zone.zones[index]),
				size,
				g_zone.zones[index]->size
			);
			if (block) {
				return block;
			}
		}
	}
	return (NULL);
}

t_block	*find_freeblock(size_t size, t_type_zone typeZone) {
	void *free_block;

	if (!g_zone.zones) {
		allocTabZones();
	}
	free_block = findBlock(size, typeZone);
	if (free_block) {
		return free_block;
	} else {
		addZone(size, typeZone);
		return findBlock(size, typeZone);
	}
}