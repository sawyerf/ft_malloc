#include <unistd.h>
#include <stdio.h>
#include "ft_malloc.h"
#include "libft.h"

void	*malloc(size_t size) {
    // ft_putstr("size: \n");
    write(1, "alae\n", 5);
    return ft_malloc(size);
}

void	free(void *ptr) {
    write(1, "free\n", 5);
    ft_free(ptr);
}