#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zones;

void	*malloc(size_t size) {
    // ft_putstr("malloc: ");
    // ft_putstr("size: ");
    // ft_putnbr(size);
    // ft_putstr("\n");
    void *ret = ft_malloc(size);
    // ft_putstr("===============\n");
    // ft_putnbr((uintptr_t)ret);
    // ft_putstr("\n");
	// light_show_zone(g_zones.tiny);
	// light_show_zone(g_zones.medium);
	// light_show_zone(g_zones.large);
    return ret;
}

void	free(void *ptr) {
    // ft_putstr("free: ");
    // ft_putnbr((uintptr_t)ptr);
    // ft_putstr("\n");
    ft_free(ptr);
}
