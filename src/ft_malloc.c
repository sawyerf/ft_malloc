#include <unistd.h>
#include <stdio.h>
#include "ft_malloc.h"

t_zones g_zones;

void	*get_zone(size_t size) {
	if (size <= MAX_SIZE_TINY) {
		if (!g_zones.tiny) {
			g_zones.tiny = alloc_zone(MAX_SIZE_TINY);
		}
		return (g_zones.tiny);
	} else if (size <= MAX_SIZE_MEDIUM) {
		if (!g_zones.medium) {
			g_zones.medium = alloc_zone(MAX_SIZE_MEDIUM);
		}
		return (g_zones.medium);
	} else {
		return (g_zones.large); // a changer
	}
}

size_t get_sizezone(size_t size) {
	if (size <= MAX_SIZE_TINY) {
		return (MAX_SIZE_TINY);
	} else if (size <= MAX_SIZE_MEDIUM) {
		return (MAX_SIZE_MEDIUM);
	} else {
		return (size);
	}
}

void	*ft_malloc(size_t size) {
	void	*zone;

	if (!size) return (NULL);
	if (!(zone = find_freeblock(get_zone(size), size, get_sizezone(size)))) return (NULL);
	set_block(zone, size);
	// light_show_zone(g_zones.tiny);
	return (zone + sizeof(t_block));
}

void	ft_free(void *ptr) {
	t_block *block;

	block = ptr - sizeof(t_block);
	// light_show_zone(g_zones.tiny);
	del_block(block);
	if (g_zones.tiny && g_zones.tiny->free && !g_zones.tiny->next) freeZone(&g_zones.tiny);
	if (g_zones.medium && g_zones.medium->free && !g_zones.medium->next) freeZone(&g_zones.medium);
	if (g_zones.large && g_zones.large->free && !g_zones.large->next) freeZone(&g_zones.large);
	// light_show_zone(g_zones.tiny);

}