/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   ft_list_remove_if.c                             :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 03:06:39 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/17 03:09:39 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
# include "libft.h"

void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(),
	__attribute__((unused)) void (*free_fct)(void *))
{
	t_list	*elem;
	t_list	*prev;
	t_list	*next;

	elem = *begin_list;
	prev = NULL;
	while (elem)
	{
		if ((*cmp)(elem->content, data_ref) == 0)
		{
			next = elem->next;
//			(*free_fct)(elem->content);
//			free(elem);
			elem = next;
			if (!prev)
				*begin_list = elem;
			else
				prev->next = elem;
		}
		else
		{
			prev = elem;
			elem = elem->next;
		}
	}
}
