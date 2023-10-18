/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 02:21:56 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"



void	*ft_malloc(size_t size)
{
	size_t				chunk_size;
	void				*chunk;
	enum chunk_size_e	chunk_type;

	chunk_type = size <= TINY_SIZE ? TINY : size <= SMALL_SIZE ? SMALL : LARGE;
	chunk_size = ALIGN(size + HEADER_SIZE);
	chunk = mmap(0, chunk_size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	msegment[chunk_type] = (malloc_segment_t *)chunk;
	msegment[chunk_type]->size = chunk_size | 1;
	msegment[chunk_type]->next = NULL;
	msegment[chunk_type]->data = (void *)((uint8_t *)chunk + HEADER_SIZE);
	return (void *)((uint8_t *)chunk + HEADER_SIZE);
}
