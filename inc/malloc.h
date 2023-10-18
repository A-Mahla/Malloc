/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 02:22:07 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MALLOC_H__
# define __MALLOC_H__


# include <stdint.h>
# include <sys/mman.h>
# include "libft.h"
# include "ft_printf.h"


# define SPACE 100
# define TINY_SIZE 128
# define SMALL_SIZE 4096
# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_SIZE (ALIGN(sizeof(size_t) + sizeof(malloc_segment_t *)))


enum chunk_size_e {
	TINY = 0,
	SMALL,
	LARGE
};

typedef struct malloc_segment_s {
	size_t					size;
	struct malloc_segment	*next;
	void					*data;
} malloc_segment_t;

static malloc_segment_t *msegment[3] __attribute__((unused));

void	show_alloc_mem(void);
// TO DELETE
void	*ft_malloc(size_t size);
/////////////


# endif
