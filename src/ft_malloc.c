#include <unistd.h>
#include <stdio.h>
#include "ft_malloc.h"
#include "libft.h"

t_zones	g_zone;


void	*ft_malloc(size_t size) {
	void	*block;

	if (!size) {
		show_alloc_mem();
		return (NULL);
	}
	if (!(block = find_freeblock(size, getSizeZone(size)))) return (NULL);
	set_block(block, size);
	return (block + sizeof(t_block));
}

void	ft_free(void *ptr) {
	if (!ptr) return ;
	removeBlock(ptr - sizeof(t_block));
	freeZone();
}

void	*ft_realloc(void *ptr, size_t size) {
	t_block *block;
	void	*new;
	size_t	prevSize;

	if (!ptr) return ft_malloc(size);
	if (!size) {
		ft_free(ptr);
		return (NULL);
	}
	block = ptr - sizeof(t_block);

	if (block->size < size) {
		prevSize = block->size;
		removeBlock(block);
		new = ft_malloc(size);
		ft_memcpy(new, ptr, prevSize);
		freeZone();
		return (new);
	} else {
		return (ptr);
	}
}