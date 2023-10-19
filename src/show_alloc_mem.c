

# include <malloc.h>

// TO DELETE
# include <stdio.h>
////////////

void	show_alloc_mem(void)
{
	size_t	size;

	printf("TINY : %p\n", hsegment[0]);
	for (header_segment_t *tmp = hsegment[TINY]; tmp; tmp = tmp->next) {
		if (tmp->size & 1) {
			size = (uint8_t *)tmp + (tmp->size & ~1L) - ((uint8_t *)tmp + HEADER_SIZE);
			printf("%p - %p", (uint8_t *)tmp + HEADER_SIZE, (uint8_t *)tmp + (tmp->size & ~1L));
			printf(" : %ld\n", size);
		}
	}
}
