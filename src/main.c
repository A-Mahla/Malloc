/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 15:43:16 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include "stdio.h"


int	main(void)
{

	char *test1 = ft_malloc(16);
	if (!test1)
		printf("test1 : WHAT !!!!");
	char *test2 = ft_malloc(16);
	if (!test2)
		printf("test2 : WHAT !!!!");
	
	ft_free(test1);
	ft_free(test2);
	return 0;
}
// 1 0001
// 0 0001
