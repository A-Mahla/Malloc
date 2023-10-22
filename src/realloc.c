/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   realloc.c                                       :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/22 03:04:52 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 04:08:24 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"


void	*ft_realloc(void *ptr, size_t size)
{
	void	*cpy;
	size_t	size_ptr;

	if (ptr != NULL && size != 0) {
		size_ptr = ((struct header_chunk *)((uint8_t *)ptr - HEADER_CHUNK_SIZE))->size;
		size_ptr &= ~1L; 
		size_ptr -= HEADER_CHUNK_SIZE;
		if (size_ptr >= size)
			return ptr;
	}
	cpy = ft_malloc(size);
	if (ptr == NULL)
		goto exit_realloc;
	if (size == 0)
		goto free_realloc;
	ft_memcpy(cpy, ptr, size);
free_realloc:
	ft_free(ptr);
exit_realloc:
	return cpy;
}
