#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include "ft_malloc.h"
#include "libft.h"

void	*malloc(size_t size) {
    debug_var("[*] malloc( size=", size, " )\n");
    void *ret = ft_malloc(size);
    return ret;
}

void	free(void *ptr) {
    debug_hex("[*] free( ptr=", ptr, " )\n");
    ft_free(ptr);
}

void	*realloc(void *ptr, size_t size) {
    debug_hex("[*] realloc( ptr=", ptr, "");
    debug_var(", size=", size, "\n");
    void *ret = ft_realloc(ptr, size);
    return ret;
}