/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/22 03:04:52 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/23 13:31:18 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"


size_t	chunk_memory_size(void *ptr, size_t size, bool *is_memory_sufficient);


/*
 * @function realloc()
 *
 * @brief entrypoint realloc() (man realloc)
 *
 * @return void*
 *
 */

void	*realloc(void *ptr, size_t size)
{
	void	*cpy = ptr;
	size_t	size_ptr;
	bool	is_memory_sufficient = false;

	size_ptr = chunk_memory_size(ptr, size, &is_memory_sufficient);
	if (is_memory_sufficient)
		goto exit_realloc;
	cpy = malloc(size);
	if (ptr == NULL || cpy == NULL)
		goto exit_realloc;
	if (size == 0)
		goto free_realloc;
	pthread_mutex_lock(&multi_threading);
	ft_memcpy(cpy, ptr, size_ptr);
	pthread_mutex_unlock(&multi_threading);
free_realloc:
	free(ptr);
exit_realloc:
	return cpy;
}


/*
 * @function check_memory_size()
 *
 * @brief check if the size of the memory chunk is sufficient
 *        for the size argument.
 *
 * @return void*
 *
 */

size_t	chunk_memory_size(void *ptr, size_t size, bool *is_memory_sufficient)
{
	size_t	size_ptr;

	pthread_mutex_lock(&multi_threading);
	size_ptr = ((struct header_chunk *)((uint8_t *)ptr
			- HEADER_CHUNK_SIZE))->size;
	size_ptr &= ~1L; 
	size_ptr -= HEADER_CHUNK_SIZE;
	if (ptr != NULL && size != 0) {
		if (size_ptr >= size)
			*is_memory_sufficient = true;
	}
	pthread_mutex_unlock(&multi_threading);
	return size_ptr;
}
