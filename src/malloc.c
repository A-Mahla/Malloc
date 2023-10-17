/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 01:20:49 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"

//static malloc_segment_t	msegment[3];


void	*ft_malloc(size_t size)
{
	size_t	chunk_size;
	void	*chunk;

	chunk_size = ALIGN(size + HEADER_SIZE);
	chunk = mmap(0, chunk_size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	*((size_t *)chunk) = chunk_size | 1;
	return (void *)((uint8_t *)chunk + HEADER_SIZE);
}
