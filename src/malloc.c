/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 17:15:31 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

void	*new_malloc(size_t size);


void	*ft_malloc(size_t size)
{
	size_t	chunk_size;
	void	*chunk;

	chunk_size = ALIGN(size + HEADER_SIZE);
	chunk = new_malloc(chunk_size);
//	return (void *)((uint8_t *)chunk + HEADER_SIZE);
	return chunk;
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


void	*new_malloc(size_t size)
{
	header_segment_t	*new_chunk;
	enum chunk_size_e	chunk_type;

	chunk_type = size <= TINY_SIZE ? TINY : size <= SMALL_SIZE ? SMALL : LARGE;
	new_chunk = mmap(0, size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	last_chunk(hsegment + chunk_type, new_chunk);
	new_chunk->size = size | 1;
	new_chunk->next = NULL;
	return (void *)((uint8_t *)new_chunk + HEADER_SIZE);
}
