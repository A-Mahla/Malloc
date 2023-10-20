/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 22:23:47 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/21 00:11:43 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"


void	free_memory(struct header_chunk *ptr);
void	remove_page(struct header_page *page);
void	group_segment(struct header_chunk *first, struct header_chunk *second);
void	coalesce(struct header_chunk *ptr);


void	ft_free(void *ptr)
{
	struct header_chunk	*tmp;

	if (!ptr)
		return;
	tmp = (struct header_chunk *)((uint8_t *)ptr - HEADER_CHUNK_SIZE);
	tmp->size &= ~1L;
	free_memory(tmp);
}


void	free_memory(struct header_chunk *chunk)
{
	chunk->current_page->nb_allocated_chunk--;
	if (!chunk->current_page->nb_allocated_chunk)
		remove_page(chunk->current_page);
	else
		coalesce(chunk);
}


void	remove_page(struct header_page *current_page)
{
	char	*error = "munmap(): error\n";

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
	if (munmap(current_page, current_page->size) < 0)
		write(1, error, ft_strlen(error));
}


void	coalesce(struct header_chunk *ptr)
{
	if (ptr->next && ptr->next->size & 1) {
		group_segment(ptr, ptr->next);
	}
	if (ptr->prev && ptr->prev->size & 1)
		group_segment(ptr->prev, ptr);
}


void	group_segment(struct header_chunk *first, struct header_chunk *second)
{
	first->size += second->size;
	first->next = second->next;
	if (second->next)
		second->next->prev = first;
}
