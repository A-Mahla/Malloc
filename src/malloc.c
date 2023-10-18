/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 18:25:43 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

void	*new_malloc(size_t size, enum chunk_size_e chunk_type);
void	last_chunk(header_segment_t **begin, header_segment_t *next);
void	split_segment(header_segment_t *to_split, size_t begin, size_t end);
void	*find_chunk_free(size_t size_chunk, enum chunk_size_e chunk_type);


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


void	*find_chunk_free(size_t chunk_size, enum chunk_size_e chunk_type)
{
	header_segment_t	*current = hsegment[chunk_type];
	size_t				current_chunk_size;

	if (!current)
		return new_malloc(chunk_size, chunk_type);
	while (current->next) {
		current_chunk_size = current->size & 1;
		if (current_chunk_size >= chunk_size) {
			split_segment(current, chunk_size, current_chunk_size - chunk_size);
			return (void *)((uint8_t *)current + HEADER_SIZE);
		}
	}
	return new_malloc(chunk_size, chunk_type);
}


void	split_segment(header_segment_t *to_split, size_t begin, size_t end)
{
	header_segment_t	*current;
	header_segment_t	*tmp;

	if (end < HEADER_SIZE)
		return;
	current = to_split;
	current->size = begin | 1;
	tmp = current->next;
	current->next = (header_segment_t *)((uint8_t *)to_split + begin);
	current = current->next;
	current->size = end;
	current->next = tmp;
}


void	*new_malloc(size_t size, enum chunk_size_e chunk_type)
{
	header_segment_t	*new_chunk;

	new_chunk = mmap(0, size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	last_chunk(hsegment + chunk_type, new_chunk);
	new_chunk->size = size | 1;
	new_chunk->next = NULL;
	return (void *)((uint8_t *)new_chunk + HEADER_SIZE);
}


void	last_chunk(header_segment_t **begin, header_segment_t *next)
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
