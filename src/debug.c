#include "ft_malloc.h"
#include "libft.h"

void puthex(unsigned long long int hex, int min) {
	char	str[23];
	char	strHex[] = "0123456789ABCDEF";
	int		index = 23;

	ft_memset(str, '0', 23);
	while (hex) {
		index--;
		str[index] = strHex[hex % 16];
		hex /= 16;
	}
	if (23 - index > min) {
		write(1, &str[index], 23 - index);
	} else {
		write(1, &str[23 - min], min);
	}
}

void debug_str(char *str) {
	if (MALLOC_DEBUG) {
		ft_putstr(str);
	}
}

void	debug_var(char *name, long long int var, char *end) {
	if (MALLOC_DEBUG) {
		ft_putstr(name);
		ft_putnbr(var);
		ft_putstr(end);
	}
}

void	debug_hex(char *name, void *var, char *end) {
	if (MALLOC_DEBUG) {
		ft_putstr(name);
		ft_putstr("0x");
		puthex((uintptr_t)var, 8);
		ft_putstr(end);
	}
}