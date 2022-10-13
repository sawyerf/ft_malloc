#include "ft_malloc.h"
#include "libft.h"

t_zones	g_zone = {0, 0, 0, 0, 0, 0, 0};

void	*ft_malloc(size_t size) {
	void	*block;
	struct rlimit rlim;

	if (!size) {
		return (NULL);
	}
	if (!g_zone.pageSize) g_zone.pageSize = getpagesize();
	if (!g_zone.maxPage) {
		if (getrlimit(RLIMIT_DATA, &rlim) < 0) return (NULL);
		g_zone.maxPage = rlim.rlim_cur / g_zone.pageSize;
	}
	size = ((size - 1) / ALIGN) * ALIGN + ALIGN;
	if (!(block = find_freeblock(size, getSizeZone(size)))) {
		return (NULL);
	}
	set_block(block, size);
	return (block + sizeof(t_block));
}

void	ft_free(void *ptr) {
	if (!ptr) return ;
	if (!checkBlock(ptr)) return ;
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
	
	if (!checkBlock(ptr)) return (NULL);
	block = ptr - sizeof(t_block);
	size = ((size - 1) / ALIGN) * ALIGN + ALIGN;
	if (block->size < size) {
		prevSize = block->size;
		removeBlock(block);
		if (!(new = find_freeblock(size, getSizeZone(size)))) {
			return (NULL);
		}
		set_block(new, size);
		new += sizeof(t_block);
		if (new != ptr)	ft_memcpy(new, ptr, prevSize);
		return (new);
	} else {
		return (ptr);
	}
}

void	*ft_calloc(size_t nmemb, size_t size) {
	if (SIZE_MAX / size < nmemb) return (NULL);
	size *= nmemb;
	void *ret = ft_malloc(size);
	if (ret) ft_bzero(ret, size);
	return ret;
}

void	*ft_reallocarray(void *ptr, size_t nmemb, size_t size) {
	if (SIZE_MAX / size < nmemb) return (NULL);
	return ft_realloc(ptr, nmemb * size);
}