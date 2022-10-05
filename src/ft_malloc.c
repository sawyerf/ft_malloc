#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include "ft_malloc.h"
#include "libft.h"

t_zones	g_zone = {0, 0, 0, NULL};
pthread_mutex_t __mutex_shared_variable = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

void	*ft_malloc(size_t size) {
	void	*block;

	pthread_mutex_lock(&__mutex_shared_variable);
	if (!size) {
		show_alloc_mem();
		return (NULL);
	}
	if (!(block = find_freeblock(size, getSizeZone(size)))) return (NULL);
	set_block(block, size);
	pthread_mutex_unlock(&__mutex_shared_variable);
	return (block + sizeof(t_block));
}

void	ft_free(void *ptr) {
	if (!ptr) return ;
	if (!checkBlock(ptr)) return ;
	pthread_mutex_lock(&__mutex_shared_variable);
	removeBlock(ptr - sizeof(t_block));
	freeZone();
	pthread_mutex_unlock(&__mutex_shared_variable);
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
	
	if (!checkBlock(ptr)) return (NULL);
	block = ptr - sizeof(t_block);
	if (block->size < size) {
		pthread_mutex_lock(&__mutex_shared_variable);
		prevSize = block->size;
		removeBlock(block);
		new = ft_malloc(size);
		ft_memcpy(new, ptr, prevSize);
		freeZone();
		pthread_mutex_unlock(&__mutex_shared_variable);
		return (new);
	} else {
		return (ptr);
	}
}