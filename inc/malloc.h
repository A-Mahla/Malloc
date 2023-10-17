/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/18 00:13:44 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MALLOC_H__
# define __MALLOC_H__

# include <stdint.h>
# include <sys/mman.h>
# include "libft.h"
# include "ft_printf.h"

# define SPACE 100
# define TINY 128
# define SMALL 4096
# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_SIZE (ALIGN(sizeof(size_t)))

typedef struct free_chunk_s {
	size_t				size;
	struct free_chunk_s	*next;
	struct free_chunk_s	*prev;
} free_chunk_t;

void	show_alloc_mem(void);

// TO DELETE
void	*ft_malloc(size_t size);


/////////////


# endif
