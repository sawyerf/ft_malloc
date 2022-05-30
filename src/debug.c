#include "ft_malloc.h"

void show_zone(void *zone) {
    t_block *block;
    size_t size;

    block = zone;
    if (!block) {
        ft_printf("\n");
        return ;
    }
    size = block->size;
    ft_printf("#%ld", block->size);
    while (--size) {
        if (!block->free) {
            ft_printf("*");
        } else {
            ft_printf(".");
        }
    }
    return show_zone(block->next);
}