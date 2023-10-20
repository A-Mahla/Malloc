

# include <malloc.h>

// TO DELETE
# include <stdio.h>
////////////

void	show_alloc_mem(void)
{
	size_t	size;

	for (struct header_page *page_nb = page[TINY]; page_nb; page_nb = page_nb->next) {
		printf("TINY : %p\n", page_nb);
		for (struct header_chunk *chunk = (struct header_chunk *)((uint8_t *)page_nb + HEADER_PAGE_SIZE); chunk; chunk = chunk->next) {
//			if (chunk->size & 1) {
				size = (uint8_t *)chunk + (chunk->size & ~1L) - ((uint8_t *)chunk + HEADER_CHUNK_SIZE);
				printf("%p - %p", (uint8_t *)chunk + HEADER_CHUNK_SIZE, (uint8_t *)chunk + (chunk->size & ~1L));
				printf(" : %ld\n", size);
//			}
		}
	}
}
