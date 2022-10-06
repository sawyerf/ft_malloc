#include "ft_malloc.h"
#include "libft.h"

void	*malloc(size_t size) {
    debug_var("[*] malloc( size=", size, " )\n");
    void *ret = ft_malloc(size);
    debug_hex("[*] ret malloc ", ret, "\n");
    return ret;
}

void	free(void *ptr) {
    debug_hex("[*] free( ptr=", ptr, " )\n");
    ft_free(ptr);
    debug_str("[*] ret free\n");
}

void	*realloc(void *ptr, size_t size) {
    debug_hex("[*] realloc( ptr=", ptr, "");
    debug_var(", size=", size, "\n");
    void *ret = ft_realloc(ptr, size);
    debug_hex("[*] ret realloc ", ret, "\n");
    return ret;
}

void *calloc(size_t nmemb, size_t size) {
    debug_var("[*] calloc( nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
    void *ret = ft_calloc(nmemb, size);
    debug_hex("[*] ret calloc ", ret, "\n");
    return ret;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size) {
    debug_hex("[*] reallocarray( ptr=", ptr, "");
    debug_var(", nmemb=", nmemb, "");
    debug_var(", size=", size, " )\n");
    void *ret = ft_reallocarray(ptr, nmemb, size);
    debug_hex("[*] ret reallocarray ", ret, "\n");
    return ret;
}