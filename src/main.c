/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 22:06:44 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include "stdio.h"


int	main(void)
{

	char *test1 = ft_malloc(16);
	if (!test1)
		printf("test1 : WHAT !!!!");
	for (int i = 0; i < 15; i++)
		test1[i] = 'A';
	test1[15] = '\0';
	printf("%s\n", test1);
	char *test2 = ft_malloc(16);
	if (!test2)
		printf("test2 : WHAT !!!!");
	for (int i = 0; i < 15; i++)
		test2[i] = 'B';
	test2[15] = '\0';
	printf("%s\n", test2);

	show_alloc_mem();
	ft_free(test1);
	ft_free(test2);
	show_alloc_mem();
	return 0;
}
// 1 0001
// 0 0001
