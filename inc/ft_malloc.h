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

typedef struct		s_block {
	size_t			size;
	unsigned int	indexZone;
	char			free;
}				t_block;

typedef struct	s_zone {
	t_type_zone	type;
	size_t		size; // size alloc - sizeof(t_zone)
}				t_zone;

typedef struct	s_zones
{
	unsigned int size;
	unsigned int numPage;
	t_zone		**zones;
}				t_zones;

void	*malloc(size_t size);
void	free(void *ptr);

void	*ft_malloc(size_t size);
void	ft_free(void *ptr);

// allocZone
void	*alloc_zone(size_t size_block);
void	set_block(t_block *block, size_t size);
void	*find_freeblock(size_t size, t_type_zone typeZone);

// freeZone
// void	del_block(void *zone);
// void	freeZone(t_block **block);

// debug
void	show_alloc_mem(void);
void	ft_putvarint(char *name, long long int var);

// zone
t_block     *getNextBlock(t_block *block);
t_block     *getFirstBlock(void *zone);
void    initZone(t_zone *zone, t_type_zone typeZone, size_t size);
void	initBlock(void *zone, size_t size, unsigned int indexZone);

#endif
