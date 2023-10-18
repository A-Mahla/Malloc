/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 02:25:24 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include "stdio.h"

//static malloc_segment_t msegment[3];


int	main(void)
{
	for (int i = TINY; i <= LARGE; i++) {
		switch (i) {
		case TINY:
			printf("type\t: TINY\n");
			break;
		case SMALL:
			printf("type\t: SMALL\n");
			break;
		case LARGE:
			printf("type\t: LARGE\n");
			break;
		}
		msegment[i].next = malloc(sizeof(malloc_segment_t *));
		printf("size\t:%zu\nnext\t:%zu\nstart\t:%zu\n", sizeof(msegment[i].size), sizeof(msegment[i].start), sizeof(msegment[i].next));
		printf("%zu", HEADER_SIZE);
	}
	ft_malloc(16);
	return 0;
}
