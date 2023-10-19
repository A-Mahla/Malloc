/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/19 19:59:24 by amahla           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MALLOC_H__
# define __MALLOC_H__


# include <stdint.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft.h"
# include "ft_printf.h"


# define PAGE 100
# define TINY_SIZE 128
# define SMALL_SIZE 1024
# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_SIZE (ALIGN(sizeof(size_t) + sizeof(header_segment_t *)))
# define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member)	\
({	\
    const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
    (type *)( (char *)__mptr - offsetof(type,member) );		\
})


enum chunk_size_e
{
	TINY = 0,
	SMALL,
	LARGE
};

typedef struct header_segment_s
{
	size_t					size;
	struct header_segment_s	*next;
} header_segment_t;

extern header_segment_t *hsegment[3];

void	show_alloc_mem(void);
// TO DELETE
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
/////////////


# endif
