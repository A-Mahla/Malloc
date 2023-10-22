/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   free.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 22:23:47 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 22:22:29 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"


void	free_memory(struct header_chunk *ptr);
void	remove_page(struct header_page *page);
void	group_segment(struct header_chunk *first, struct header_chunk *second);
void	coalesce(struct header_chunk *ptr);
bool	is_last_page(struct header_page *current_page);


/*
 * @function free()
 *
 * @brief entrypoint deallocator
 *
 * @return void
 *
 */

void	free(void *ptr)
{
	struct header_chunk	*tmp;

	if (!ptr)
		return;
	pthread_mutex_lock(&multi_threading);
	tmp = (struct header_chunk *)((uint8_t *)ptr - HEADER_CHUNK_SIZE);
	tmp->size &= ~1L;
	free_memory(tmp);
	pthread_mutex_unlock(&multi_threading);
}


/*
 * @function free_memory()
 *
 * @brief this function decremente nb_allocated_chunk in the corresponding 
 *
 * @return void
 *
 */

void	free_memory(struct header_chunk *chunk)
{
	chunk->current_page->nb_allocated_chunk--;
	coalesce(chunk);
	if (!chunk->current_page->nb_allocated_chunk)
		remove_page(chunk->current_page);
}


/*
 * @function remove_page()
 *
 * @brief munmap if is an empty page 
 *
 * @return void
 *
 */

void	remove_page(struct header_page *current_page)
{
	if (is_last_page(current_page))
		return;
	if (!current_page->prev) {
		if (current_page == page[TINY])
			page[TINY] = current_page->next;
		else if (current_page == page[SMALL])
			page[SMALL] = current_page->next;
		else if (current_page == page[LARGE])
			page[LARGE] = current_page->next;
	} else {
		current_page->prev->next = current_page->next;
	}
	if (current_page->next)
			current_page->next->prev = current_page->prev;
	munmap(current_page, current_page->size);
}


/*
 * @function coalesce()
 *
 * @brief merge free neighbors chunks 
 *
 * @return void
 *
 */

void	coalesce(struct header_chunk *ptr)
{
	if (ptr->next && !(ptr->next->size & 1))
		group_segment(ptr, ptr->next);
	if (ptr->prev && !(ptr->prev->size & 1))
		group_segment(ptr->prev, ptr);
}


/*
 * @function coalesce()
 *
 * @brief merge two chunks
 *
 * @return void
 *
 */

void	group_segment(struct header_chunk *first, struct header_chunk *second)
{
	first->size += second->size;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
}


/*
 * @function is_last_page()
 *
 * @brief  check if is last page of a given chunk type
 *
 * @return bool
 *
 */


bool	is_last_page(struct header_page *current_page)
{
	bool is_last = false;

	if (current_page == page[TINY] || current_page == page[SMALL]) {
		if (!current_page->next)
			is_last = true;
	}
	return is_last;
}
