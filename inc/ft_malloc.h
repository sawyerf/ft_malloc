#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include "ft_printf.h"

# define MAX_SIZE_TINY 32
# define MAX_SIZE_MEDIUM 64

typedef struct	s_zones
{
	void		*tiny;
	void		*medium;
	void		*large;
}				t_zones;

typedef struct	s_block {
	// size_t		size_prev;
	size_t		size;
	struct	s_block	*prev;
	struct	s_block	*next;
	char		free;
}				t_block;

void	*ft_malloc(size_t size);
void	*alloc_zone(size_t size_block);
void 	show_zone(void *zone);

void	set_block(void *zone, size_t size);
void	del_block(void *zone);
void	*find_block(void *zone, size_t size);
#endif