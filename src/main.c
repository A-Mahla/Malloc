/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 13:35:00 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 18:01:53 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "malloc.h"
# include "stdio.h"


int	main(void)
{
	ft_malloc(16);
	ft_malloc(16);
	printf("%d", 16 | 1);
	return 0;
}
// 1 0001
// 0 0001
