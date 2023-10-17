/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.c                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:00:36 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/17 22:21:28 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"


void	*ft_malloc(size_t size)
{
	size_t	chunk_size;
	void	*chunk;

	chunk_size = ALIGN(size + HEADER_SIZE);
	chunk = mmap(0, chunk_size, PROT_READ | PROT_WRITE,
				 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	*((uintptr_t *)chunk) = chunk_size | 1;
	return chunk;
}
