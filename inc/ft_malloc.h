#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>

# define MAX_SIZE_TINY 256
# define MAX_SIZE_MEDIUM 2048

# define TYPE_TINY 1
# define TYPE_MEDIUM 2
# define TYPE_LARGE 3

typedef enum e_type_zone
{
	unused = 0,
	tiny,
	medium,
	large
}			t_type_zone;

typedef struct	s_zones
{
	unsigned int size;
	unsigned int numPage;
	t_zone		**zones;
}				t_zones;

typedef struct	s_zone {
	t_type_zone	type;
	size_t		size;
}				t_zone;

typedef struct		s_block {
	size_t			size;
	unsigned int	zone;
	char			free;
}				t_block;


void	*malloc(size_t size);
void	free(void *ptr);

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

void	*alloc_zone(size_t size_block);
void	set_block(void *zone, size_t size);
void	del_block(void *zone);
void	*find_block(void *zone, size_t size);
void	*find_freeblock(void *zone, size_t size, size_t page_size);
void	freeZone(t_block **block);

void	show_alloc_mem(void);
void 	showBlocks(void *zone);

#endif
