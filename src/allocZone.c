#include "ft_malloc.h"
#include "libft.h"

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

static void	*secuMmap(size_t size) {
	int nbPage = size / g_zone.pageSize;

	debug_var("[*] mmap( size=", size, " )");
	debug_var(" page=", nbPage, "");
	debug_var(", pageAlloc=", g_zone.pageAlloc, "");
	debug_var(", maxPage=", g_zone.maxPage, "\n");
	if (g_zone.maxPage < g_zone.pageAlloc + nbPage) {
		debug_var("Limit of memory, can't mmap. ( maxPage=", g_zone.maxPage, "");
		debug_var(", pageAlloc=", g_zone.pageAlloc, " )");
		return (NULL);
	}
	g_zone.pageAlloc += nbPage;
	return mmap(NULL,
		size,
		PROT_READ | PROT_WRITE,
		MAP_ANONYMOUS|MAP_PRIVATE,
		-1,
		0
	);
}

static void	*allocZone(size_t sizeBlock, t_type_zone typeZone) {
	t_zone	*zone;
	size_t	real_size;
	
	debug_var("[*] allocZone( sizeBlock=", sizeBlock, "");
	debug_var(", typeZone=", typeZone, " )\n");
	if (typeZone == tiny) {
		sizeBlock = MAX_SIZE_TINY;
	} else if (typeZone == small) {
		sizeBlock = MAX_SIZE_SMALL;
	}
	real_size = (sizeBlock + sizeof(t_block));
	if (typeZone != large) {
		real_size *= 100;
	}
	real_size += sizeof(t_zone);
	real_size = ((real_size - 1) / g_zone.pageSize) * g_zone.pageSize + g_zone.pageSize;
	if (!(zone = secuMmap(real_size))) return (NULL);
	initZone(zone, typeZone, real_size - sizeof(t_zone));
	initBlock(getFirstBlock(zone), real_size - sizeof(t_zone) - sizeof(t_block), 0);
	return (zone);
}

static void	allocTabZones() {
	t_zone	**newZones;

	debug_var("[*] Alloc Tab Zone ( numPage=", g_zone.numPage + 1, " )\n");
	if (!(newZones = secuMmap((g_zone.numPage + 1) * g_zone.pageSize))) return ;
	if (g_zone.zones) {
		ft_memcpy(newZones, g_zone.zones, g_zone.numPage * g_zone.pageSize);
		secuMunmap(g_zone.zones, g_zone.numPage * g_zone.pageSize);
	}
	g_zone.numPage++;
	g_zone.size = (g_zone.numPage * g_zone.pageSize) / sizeof(t_zone*);
	g_zone.zones = newZones;
}

static int addZoneToTab(t_zone *zone) {
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

static void	addZone(size_t size, t_type_zone typeZone) {
	t_zone	*new;

	if (!(new = allocZone(size, typeZone))) return ;
	if (!addZoneToTab(new)) {
		allocTabZones();
		addZoneToTab(new);
	}
}

static t_block	*findFreeBlock(t_block *block, size_t size, size_t sizeZone) {
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

static void	*findBlock(size_t size, t_type_zone typeZone) {
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