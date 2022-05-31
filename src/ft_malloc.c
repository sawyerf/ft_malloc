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

void	*ft_malloc(size_t size) {
	void	*zone;

	if (!size) return (NULL);
	zone = find_block(get_zone(size), size);
	if (!zone) return (NULL);
	set_block(zone, size);
	// show_zone(g_zones.tiny);
	return (zone + sizeof(t_block));
}

void	ft_free(void *ptr) {
	t_block *block;

	block = ptr - sizeof(t_block);
	del_block(block);
}