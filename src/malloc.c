/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 21:15:45 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

void	*new_malloc(size_t size, enum chunk_size_e chunk_type);
void	push_back_chunk(header_segment_t **begin, header_segment_t *next);
void	split_segment(header_segment_t *to_split, size_t begin, size_t end);
void	*find_chunk_free(size_t size_chunk, enum chunk_size_e chunk_type);

header_segment_t *hsegment[3] = {NULL, NULL, NULL};


/*
 * @function ft_malloc()
 *
 * @brief entrypoint allocator
 *
 * @return void*
 *
 */

void	*ft_malloc(size_t size)
{
	size_t	chunk_size;
	enum	chunk_size_e	chunk_type;
	void	*chunk;

	chunk_size = ALIGN(size + HEADER_SIZE);
	chunk_type = chunk_size <= TINY_SIZE ? TINY : chunk_size <= SMALL_SIZE ? SMALL : LARGE;
	chunk = find_chunk_free(chunk_size, chunk_type);
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
	header_segment_t	*current = hsegment[chunk_type];
	size_t				current_chunk_size;

	if (!current) {
		return new_malloc(chunk_size, chunk_type);
	}
	while (current) {
		current_chunk_size = current->size & ~1L;
		if (current_chunk_size >= chunk_size && !(current->size & 1)) {
			split_segment(current, chunk_size, current_chunk_size - chunk_size);
			return (void *)((uint8_t *)current + HEADER_SIZE);
		}
		current = current->next;
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

void	split_segment(header_segment_t *to_split, size_t begin, size_t end)
{
	header_segment_t	*current;
	header_segment_t	*tmp;

	if (end < HEADER_SIZE)
		return;
	current = to_split;
	current->size = begin | 1;
	tmp = current;
	current = (header_segment_t *)((uint8_t *)to_split + begin);
	current->size = end;
	current->next = tmp->next;
	tmp->next = current;
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
	header_segment_t	*new_chunk;
	size_t				mmap_size_to_alloc;

	switch (chunk_type) {
		case TINY:
			mmap_size_to_alloc = (TINY_SIZE * 100) & ~(getpagesize() - 1);
			break;
		case SMALL:
			mmap_size_to_alloc = (SMALL_SIZE * 100) & ~(getpagesize() - 1);
			break;
		default:
			mmap_size_to_alloc = size;
	}
	new_chunk = mmap(0, mmap_size_to_alloc, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (new_chunk == MAP_FAILED)
		return NULL;
	new_chunk->next = NULL;
	push_back_chunk(hsegment + chunk_type, new_chunk);
	split_segment(new_chunk, size, mmap_size_to_alloc - size);
	return (void *)((uint8_t *)new_chunk + HEADER_SIZE);
}


/*
 * @function push_back_chunk()
 *
 * @brief push back the (*next) in the (**begin) chunk list.
 *
 * @return void
 *
 */

void	push_back_chunk(header_segment_t **begin, header_segment_t *next)
{
	header_segment_t	*current = *begin;

	if (!current){
		*begin = next;
		return;
	}
	while (current->next)
		current = current->next;
	current->next = next;
}
