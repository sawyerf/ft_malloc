#include "ft_malloc.h"
#include "libft.h"

pthread_mutex_t __mutex_shared_variable = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size) {
	pthread_mutex_lock(&__mutex_shared_variable);
    debug_var("[*] malloc( size=", size, " )\n");
    void *ret = ft_malloc(size);
    debug_hex("[*] ret malloc ", ret, "\n");
	pthread_mutex_unlock(&__mutex_shared_variable);
    return ret;
}

void	free(void *ptr) {
	pthread_mutex_lock(&__mutex_shared_variable);
    debug_hex("[*] free( ptr=", ptr, " )\n");
    ft_free(ptr);
    debug_str("[*] ret free\n");
	pthread_mutex_unlock(&__mutex_shared_variable);
}

void	*realloc(void *ptr, size_t size) {
	pthread_mutex_lock(&__mutex_shared_variable);
    debug_hex("[*] realloc( ptr=", ptr, "");
    debug_var(", size=", size, "\n");
    void *ret = ft_realloc(ptr, size);
    debug_hex("[*] ret realloc ", ret, "\n");
	pthread_mutex_unlock(&__mutex_shared_variable);
    return ret;
}

void *calloc(size_t nmemb, size_t size) {
	pthread_mutex_lock(&__mutex_shared_variable);
    debug_var("[*] calloc( nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
    void *ret = ft_calloc(nmemb, size);
    debug_hex("[*] ret calloc ", ret, "\n");
	pthread_mutex_unlock(&__mutex_shared_variable);
    return ret;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
	pthread_mutex_lock(&__mutex_shared_variable);
    debug_hex("[*] reallocarray( ptr=", ptr, "");
    debug_var(", nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
    void *ret = ft_reallocarray(ptr, nmemb, size);
    debug_hex("[*] ret reallocarray ", ret, "\n");
	pthread_mutex_unlock(&__mutex_shared_variable);
    return ret;
}