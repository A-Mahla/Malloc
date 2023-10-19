/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 22:23:47 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 22:54:01 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "malloc.h"
# include <stdbool.h>

// TO DELETE
# include <stdio.h>
//

void	free_memory(header_segment_t *ptr);
bool	page_empty(header_segment_t *ptr);

void	ft_free(void *ptr)
{
	header_segment_t	*tmp;

	if (!ptr)
		return;
	tmp = (header_segment_t *)((uint8_t *)ptr - HEADER_SIZE);
	tmp->size &= ~1L;

	printf("%p\n", container_of(&tmp, header_segment_t, next));
//	if (page_empty(tmp))
//		printf("BEGIN\n");
//	else
//		printf("END\n");
//	free_memory((header_segment_t *)tmp);
}

//bool	page_empty(header_segment_t *ptr) {
//	if (((ptr == hsegment[TINY] || ptr == hsegment[TINY]
//					|| ptr == hsegment[LARGE]) && !(ptr->size & 1))
//			|| (ptr->next == NULL && !(ptr->size & 1)))
//		return true;
//	if (ptr->size & 1) {
//		return false;
//	}
//	return page_empty(container_of(&ptr, header_segment_t, next));

//	if (((ptr == hsegment[TINY] || ptr == hsegment[TINY]
//					|| ptr == hsegment[LARGE]) && !(ptr->size & 1))
//			|| (ptr->next == NULL && !(ptr->size & 1)))
//		return 0;
//	else if (ptr->size & 1)
//		return 1;
//	return (page_empty(container_of(&ptr, header_segment_t, next)) == 1) == page_empty(ptr->next);
//}

//void	free_memory(header_segment_t *ptr)
//{
//	header_segment_t	*tmp;
//	char				*error = "munmap(): error\n";
//
//	if (ptr == hsegment[TINY]) {
//		hsegment[TINY] = ptr->next;
//	} else if (ptr == hsegment[SMALL]) {
//		hsegment[SMALL] = ptr->next;
//	} else if (ptr == hsegment[LARGE]) {
//		hsegment[LARGE] = ptr->next;
//	} else {
//		tmp = container_of(&ptr, header_segment_t, next);
//		tmp->next = ptr->next;
//	}
//	if (munmap(ptr, ptr->size) < 0)
//		write(1, error, ft_strlen(error));
//}
