/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 01:27:50 by amahla ###       ########     ########   */
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
# define HEADER_SIZE (ALIGN(sizeof(size_t)))


enum chunk_size_e {
	TINY = 0,
	SMALL,
	LARGE
};

typedef struct malloc_segment_s {
	size_t					size;
	void					*start;
	struct malloc_segment	*next;
} malloc_segment_t;

typedef struct free_chunk_s {
	size_t				size;
	struct free_chunk_s	*next;
	struct free_chunk_s	*prev;
} free_chunk_t;

static malloc_segment_t msegment[3] __attribute__((unused));

void	show_alloc_mem(void);
// TO DELETE
void	*ft_malloc(size_t size);
/////////////


# endif
