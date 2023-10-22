/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 04:13:16 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include "stdio.h"


int	main(void)
{

	char *test1 = ft_malloc(32);
	if (!test1)
		printf("test1 : WHAT !!!!");
	for (int i = 0; i < 15; i++)
		test1[i] = 'A';
	test1[15] = '\0';
	char *test2 = ft_malloc(13);
	if (!test2)
		printf("test2 : WHAT !!!!");
	for (int i = 0; i < 13; i++)
		test2[i] = 'B';
	test2[13] = '\0';
	printf("%s\n", test2);
//	char *test3 = ft_malloc(500);
//	char *test4 = ft_malloc(907);
//	char *test5 = ft_malloc(1024);
//	char *test6 = ft_malloc(2000);
//	char *test7 = ft_malloc(5000);



	show_alloc_mem();
	ft_free(test1);
	show_alloc_mem();
////	ft_free(test2);
////	show_alloc_mem();
//	ft_free(test4);
//	show_alloc_mem();
//	ft_free(test5);
//	show_alloc_mem();
//	ft_free(test3);
//	show_alloc_mem();
//	ft_free(test6);
//	show_alloc_mem();
//	ft_free(test7);
//	show_alloc_mem();

	test2 = ft_realloc(test2, 17);
//	printf("%s\n", test2);
	show_alloc_mem();
	return 0;
}
// 1 0001
// 0 0001
