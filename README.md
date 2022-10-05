# 💾 ft_malloc

Reproduction de la celebre fonction malloc

```c
// ft_printf("next: %p\n", block->next);
// ft_printf("prev: %p\n", block->prev);
// ft_printf("prev: %p\n", (block->next)->prev);
// ft_printf("size: %d\n", block->size);
// ft_printf("next: %p\n", );
```

## Schema Zone
```
+-------------------------------+---------+
| Metadata                      | Data    |
+------+------+--------+--------+---------+
| size        | isfree | indexP | Hex     |
+------+------+--------+--------+---------+
```
```
+--------------+---------+--------------+---------+
| Metadata     | Data    | Metadata     | Data    |
+--------------+---------+--------------+---------+
```

## Links
- [Subject](https://cdn.intra.42.fr/pdf/pdf/48936/fr.subject.pdf)
- [Malloc Tutorial](https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf)
- [Source malloc](https://code.woboq.org/userspace/glibc/malloc/malloc.c.html)
- [Thread example](https://gist.github.com/gustavorv86/51582381d4aaa5efe837a0a4a9daf663)