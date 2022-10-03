#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

void	*malloc(size_t size) {
    void *ret = ft_malloc(size);
    return ret;
}

void	free(void *ptr) {
    ft_free(ptr);
}

void	*realloc(void *ptr, size_t size) {
    return ft_realloc(ptr, size);
}