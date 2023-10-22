/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 04:05:59 by amahla ###       ########     ########   */
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
# define HEADER_CHUNK_SIZE (ALIGN(sizeof(struct header_chunk)))
# define HEADER_PAGE_SIZE (ALIGN(sizeof(struct header_page)))
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

struct header_chunk
{
	size_t				size;
	struct header_chunk	*next;
	struct header_chunk	*prev;
	struct header_page	*current_page;
};

struct header_page
{
	size_t				size;
	struct header_page	*next;
	struct header_page	*prev;
	size_t				nb_allocated_chunk;
};

extern struct header_page *page[3];

void	show_alloc_mem(void);
// TO DELETE
void	*ft_malloc(size_t size);
void	ft_free(void *ptr);
void	*ft_realloc(void *ptr, size_t size);
# include <stdio.h>
/////////////


# endif
