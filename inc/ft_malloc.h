#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdint.h>
# include <pthread.h>

# define MAX_SIZE_TINY 256
# define MAX_SIZE_SMALL 1024

typedef enum e_type_zone
{
	unused = 0,
	tiny,
	small,
	large
}			t_type_zone;

typedef enum e_debug
{
	notset = 0,
	activate,
	desactivate,
}			t_debug;

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
	unsigned long long int pageAlloc;
	unsigned int size;
	unsigned int numPage;
	size_t		pageSize;
	size_t		maxPage;
	t_debug		 debug;	
	t_zone		**zones;
}				t_zones;

extern t_zones g_zone;

// malloc
extern void	*malloc(size_t size);
extern void	free(void *ptr);
extern void	*realloc(void *ptr, size_t size);
extern void	*calloc(size_t nmemb, size_t size);
extern void	*reallocarray(void *ptr, size_t nmemb, size_t size);

// ft_malloc
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_reallocarray(void *ptr, size_t nmemb, size_t size);

// allocZone
void	set_block(t_block *block, size_t size);
t_block	*find_freeblock(size_t size, t_type_zone typeZone);

// freeZone
void	secuMunmap(void *ptr, size_t size);
int		checkBlock(void *data);
void	freeZone();
void	removeBlock(t_block *zone);

// show_alloc_mem
extern void	show_alloc_mem(void);
extern void	show_alloc_mem_ex(void);

// debug
void	puthex(unsigned long long int hex, int min);
void	debug_str(char *str);
void	debug_var(char *name, long long int var, char *end);
void	debug_hex(char *name, void *var, char *end);

// zone
t_block		*getNextBlock(t_block *block);
t_block		*getFirstBlock(void *zone);
void		initZone(t_zone *zone, t_type_zone typeZone, size_t size);
void		initBlock(void *zone, size_t size, unsigned int indexZone);
int			isLastBlock(t_block *block);
t_block		*getPrevBlock(t_block *block);
int			getSizeZone(size_t size);

#endif
