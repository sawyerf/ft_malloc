#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include "ft_printf.h"

# define MAX_SIZE_TINY 32
# define MAX_SIZE_MEDIUM 64

# define TYPE_TINY 1
# define TYPE_MEDIUM 2
# define TYPE_LARGE 3

typedef struct	s_zone {
	void		*zone;
	char		type;
}				t_zone;

typedef struct		s_block {
	// size_t		size_prev;
	size_t			size;
	struct	s_block	*prev;
	struct	s_block	*next;
	void			*zone;
	char			free;
}				t_block;

typedef struct	s_zones
{
	t_block		*tiny;
	t_block		*medium;
	t_block		*large;
}				t_zones;

void	*ft_malloc(size_t size);
void	*alloc_zone(size_t size_block);
void 	show_zone(void *zone);
void 	light_show_zone(void *zone);

void	set_block(void *zone, size_t size);
void	del_block(void *zone);
void	*find_block(void *zone, size_t size);
void	ft_free(void *ptr);
void	*find_freeblock(void *zone, size_t size, size_t page_size);
void	freeZone(t_block **block);
#endif