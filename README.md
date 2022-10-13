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

## Malloc Rule
```
  The main properties of the algorithms are:
  * For large (>= 512 bytes) requests, it is a pure best-fit allocator,
    with ties normally decided via FIFO (i.e. least recently used).
  * For small (<= 64 bytes by default) requests, it is a caching
    allocator, that maintains pools of quickly recycled chunks.
  * In between, and for combinations of large and small requests, it does
    the best it can trying to meet both goals at once.
  * For very large requests (>= 128KB by default), it relies on system
    memory mapping facilities, if supported.

  Alignment:                              2 * sizeof(size_t) (default)
       (i.e., 8 byte alignment with 4byte size_t). This suffices for
       nearly all current machines and C compilers. However, you can
       define MALLOC_ALIGNMENT to be wider than this if necessary.
  Minimum overhead per allocated chunk:   4 or 8 bytes
       Each malloced chunk has a hidden word of overhead holding size
       and status information.
  Minimum allocated size: 4-byte ptrs:  16 bytes    (including 4 overhead)
			  8-byte ptrs:  24/32 bytes (including, 4/8 overhead)
       When a chunk is freed, 12 (for 4byte ptrs) or 20 (for 8 byte
       ptrs but 4 byte size) or 24 (for 8/8) additional bytes are
       needed; 4 (8) for a trailing size field and 8 (16) bytes for
       free list pointers. Thus, the minimum allocatable size is
       16/24/32 bytes.
       Even a request for zero bytes (i.e., malloc(0)) returns a
       pointer to something of the minimum allocatable size.
       The maximum overhead wastage (i.e., number of extra bytes
       allocated than were requested in malloc) is less than or equal
       to the minimum size, except for requests >= mmap_threshold that
       are serviced via mmap(), where the worst case wastage is 2 *
       sizeof(size_t) bytes plus the remainder from a system page (the
       minimal mmap unit); typically 4096 or 8192 bytes.
  Maximum allocated size:  4-byte size_t: 2^32 minus about two pages
			   8-byte size_t: 2^64 minus about two pages
```

## Commands
```
(for i in {1..100} ; do ./inject.sh time -v ~/ft_malloc/test 2>&1 | grep Minor | grep Minor; done ) | sort -u
```

## Links
- [Subject](https://cdn.intra.42.fr/pdf/pdf/48936/fr.subject.pdf)
- [Malloc Tutorial](https://wiki-prog.infoprepa.epita.fr/images/0/04/Malloc_tutorial.pdf)
- [Source malloc](https://code.woboq.org/userspace/glibc/malloc/malloc.c.html)
- [Thread example](https://gist.github.com/gustavorv86/51582381d4aaa5efe837a0a4a9daf663)