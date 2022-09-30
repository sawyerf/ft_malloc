#include <unistd.h>
#include <stdio.h>
#include "ft_malloc.h"

t_zones	g_zone = NULL;

int	get_sizezone(size_t size) {
	if (size <= MAX_SIZE_TINY) {
		return (tiny);
	} else if (size <= MAX_SIZE_MEDIUM) {
		return (medium);
	} else {
		return (large);
	}
}

void	*ft_malloc(size_t size) {
	void	*zone;

	if (!size) return (NULL);
	if (!(zone = find_freeblock(size, get_sizezone(size)))) return (NULL);
	set_block(zone, size);
	return (zone + sizeof(t_block));
}

void	ft_free(void *ptr) {
	t_block *block;

	if (!ptr) return ;
	block = ptr - sizeof(t_block);
	del_block(block);
	// if (g_zones.tiny && g_zones.tiny->free && !g_zones.tiny->next) freeZone(&g_zones.tiny);
	// if (g_zones.medium && g_zones.medium->free && !g_zones.medium->next) freeZone(&g_zones.medium);
	// if (g_zones.large && g_zones.large->free && !g_zones.large->next) freeZone(&g_zones.large);
}