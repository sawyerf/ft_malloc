#include <stdio.h>
#include <unistd.h>
#include "ft_malloc.h"

int main() {
	printf("%d\n", getpagesize());
	ft_malloc(12);
}