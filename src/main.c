/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                          :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 01:27:27 by amahla ###       ########     ########   */
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
		printf("size\t:%zu\nstart\t:%p\nnext\t:%p\n", msegment[i].size, msegment[i].start, msegment[i].next);
	}
	return 0;
}
