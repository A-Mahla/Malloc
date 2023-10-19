/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 22:23:47 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 15:43:06 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"

void	free_memory(header_segment_t *ptr);

void	ft_free(void *ptr)
{
	uint8_t	*tmp;

	if (!ptr)
		return;
	tmp = (uint8_t *)ptr - HEADER_SIZE;
	*((size_t *)tmp) &= ~1L;
	free_memory((header_segment_t *)tmp);
}

void	free_memory(header_segment_t *ptr)
{
	header_segment_t	*tmp;
	char				*error = "munmap(): error\n";

	if (ptr == hsegment[TINY]) {
		hsegment[TINY] = ptr->next;
	} else if (ptr == hsegment[SMALL]) {
		hsegment[SMALL] = ptr->next;
	} else if (ptr == hsegment[LARGE]) {
		hsegment[LARGE] = ptr->next;
	} else {
		tmp = container_of(&ptr->next, header_segment_t, next);
		tmp->next = ptr->next;
	}
	if (munmap(ptr, ptr->size) < 0)
		write(1, error, ft_strlen(error));
}
