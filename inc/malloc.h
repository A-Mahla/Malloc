/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 16:31:36 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MALLOC_H__
# define __MALLOC_H__


# include <stdint.h>
# include <sys/mman.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include "libft.h"


# define PAGE 100
# define TINY_SIZE 128
# define SMALL_SIZE 1024
# define ALIGNMENT 16
# define ALIGN(size) (((size) + (ALIGNMENT - 1)) & ~(ALIGNMENT - 1))
# define HEADER_CHUNK_SIZE (ALIGN(sizeof(struct header_chunk)))
# define HEADER_PAGE_SIZE (ALIGN(sizeof(struct header_page)))


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

extern struct header_page	*page[3];
extern pthread_mutex_t		multi_threading;

void	show_alloc_mem(void);

# endif
