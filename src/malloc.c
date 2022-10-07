#include "ft_malloc.h"
#include "libft.h"
#include <pthread.h>

pthread_mutex_t __mutex_shared_variable = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size) {
    debug_var("[*] malloc( size=", size, " )\n");
	pthread_mutex_lock(&__mutex_shared_variable);
    void *ret = ft_malloc(size);
	pthread_mutex_unlock(&__mutex_shared_variable);
    debug_hex("[*] ret malloc ", ret, "\n");
    return ret;
}

void	free(void *ptr) {
    debug_hex("[*] free( ptr=", ptr, " )\n");
	pthread_mutex_lock(&__mutex_shared_variable);
    ft_free(ptr);
	pthread_mutex_unlock(&__mutex_shared_variable);
    debug_str("[*] ret free\n");
}

void	*realloc(void *ptr, size_t size) {
    debug_hex("[*] realloc( ptr=", ptr, "");
    debug_var(", size=", size, "\n");
	pthread_mutex_lock(&__mutex_shared_variable);
    void *ret = ft_realloc(ptr, size);
	pthread_mutex_unlock(&__mutex_shared_variable);
    debug_hex("[*] ret realloc ", ret, "\n");
    return ret;
}

void *calloc(size_t nmemb, size_t size) {
    debug_var("[*] calloc( nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
	pthread_mutex_lock(&__mutex_shared_variable);
    void *ret = ft_calloc(nmemb, size);
	pthread_mutex_unlock(&__mutex_shared_variable);
    debug_hex("[*] ret calloc ", ret, "\n");
    return ret;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
    debug_hex("[*] reallocarray( ptr=", ptr, "");
    debug_var(", nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
	pthread_mutex_lock(&__mutex_shared_variable);
    void *ret = ft_reallocarray(ptr, nmemb, size);
	pthread_mutex_unlock(&__mutex_shared_variable);
    debug_hex("[*] ret reallocarray ", ret, "\n");
    return ret;
}