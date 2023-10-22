/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 21:57:48 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

void	*new_malloc(size_t size, enum chunk_size_e chunk_type);
void	push_back_page(struct header_page **begin, struct header_page *next);
void	split_segment(struct header_chunk *to_split, size_t begin, size_t end);
void	*find_chunk_free(size_t size_chunk, enum chunk_size_e chunk_type);

struct header_page *page[3] = {NULL, NULL, NULL};
pthread_mutex_t		multi_threading = PTHREAD_MUTEX_INITIALIZER;


/*
 * @function malloc()
 *
 * @brief entrypoint allocator
 *
 * @return void*
 *
 */

// CHANGE TO malloc()
void	*malloc(size_t size)
{
	size_t	chunk_size;
	enum	chunk_size_e	chunk_type;
	void	*chunk;

	if (!size)
		return NULL;
	pthread_mutex_lock(&multi_threading);
	chunk_type = size <= TINY_SIZE ? TINY : size <= SMALL_SIZE ? SMALL : LARGE;
	chunk_size = ALIGN(size + HEADER_CHUNK_SIZE);
	chunk = find_chunk_free(chunk_size, chunk_type);
	pthread_mutex_unlock(&multi_threading);
	return chunk;
}


/*
 * @function find_chunk_free()
 *
 * @brief find a chunk freed or call new_malloc() to mmap a new page.
 *
 * @return void*
 *
 */

void	*find_chunk_free(size_t chunk_size, enum chunk_size_e chunk_type)
{
	struct header_page	*current_page;
	struct header_chunk	*current_chunk;
	size_t				current_chunk_size;

	current_page = page[chunk_type];
	while (current_page) {
		current_chunk = (struct header_chunk *)((uint8_t *)current_page + HEADER_PAGE_SIZE);
		while (current_chunk) {
			current_chunk_size = current_chunk->size & ~1L;
			if (current_chunk_size >= chunk_size && !(current_chunk->size & 1)) {
				current_page->nb_allocated_chunk++;
				current_chunk->current_page = current_page;
				split_segment(current_chunk, chunk_size, current_chunk_size - chunk_size);
				return (void *)((uint8_t *)current_chunk + HEADER_CHUNK_SIZE);
			}
			current_chunk = current_chunk->next;
		}
		current_page = current_page->next;
	}
	return new_malloc(chunk_size, chunk_type);
}


/*
 * @function split_segment()
 *
 * @brief split the current memory chunk to fit to the size give to malloc.
 *
 * @return void
 *
 */

void	split_segment(struct header_chunk *to_split, size_t begin, size_t end)
{
	struct header_chunk	*current;
	struct header_chunk	*tmp;

	current = to_split;
	current->size = begin | 1;
	if (end < HEADER_CHUNK_SIZE)
		return;
	tmp = current;
	current = (struct header_chunk *)((uint8_t *)to_split + begin);
	current->size = end;
	tmp->next = current;
	current->prev = tmp;
	current->current_page = tmp->current_page;
}


/*
 * @function new_malloc()
 *
 * @brief allocate a new memory page to increase available memory in the process.
 *
 * @return void*
 *
 */

void	*new_malloc(size_t size, enum chunk_size_e chunk_type)
{
	struct header_page	*new_page;
	struct header_chunk	*new_chunk;
	size_t				mmap_size_to_alloc;

	switch (chunk_type) {
		case TINY:
			mmap_size_to_alloc = ((TINY_SIZE + HEADER_CHUNK_SIZE) * 100) + HEADER_PAGE_SIZE;
			break;
		case SMALL:
			mmap_size_to_alloc = ((SMALL_SIZE + HEADER_CHUNK_SIZE) * 100) + HEADER_PAGE_SIZE;
			break;
		default:
			mmap_size_to_alloc = size + HEADER_PAGE_SIZE;
	}
	mmap_size_to_alloc = (mmap_size_to_alloc + (getpagesize() - 1)) & ~(getpagesize() - 1);
	new_page = mmap(0, mmap_size_to_alloc, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_page == MAP_FAILED)
		return NULL;
	new_page->size = mmap_size_to_alloc;
	push_back_page(page + chunk_type, new_page);
	new_chunk = (struct header_chunk *)((uint8_t *)new_page + HEADER_PAGE_SIZE);
	split_segment(new_chunk, size, mmap_size_to_alloc - size);
	new_chunk->prev = NULL;
	new_chunk->current_page = new_page;
	return (void *)((uint8_t *)new_chunk + HEADER_CHUNK_SIZE);
}


/*
 * @function push_back_chunk()
 *
 * @brief push back the (*next) in the (**begin) chunk list.
 *
 * @return void
 *
 */

void	push_back_page(struct header_page **begin, struct header_page *next)
{
	struct header_page	*current = *begin;

	next->next = NULL;
	next->prev = NULL;
	next->nb_allocated_chunk = 1;
	if (!current){
		*begin = next;
		return;
	}
	while (current->next)
		current = current->next;
	current->next = next;
	next->prev = current;
}
