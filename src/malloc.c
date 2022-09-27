#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

extern t_zones g_zones;

void	*malloc(size_t size) {
    void *ret = ft_malloc(size);
    // show_alloc_mem();
    return ret;
}

void	free(void *ptr) {
    // show_alloc_mem();
    ft_free(ptr);
}
