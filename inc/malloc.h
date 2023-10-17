/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   malloc.h                                        :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/17 01:42:58 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/17 02:17:45 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# ifndef __MALLOC_H__
# define __MALLOC_H__

# include "libft.h"
# include "printf.h"

# define TINY 128
# define SMALL 4096

#define offsetof(TYPE, MEMBER) ((size_t)&((TYPE *)0)->MEMBER)
#define container_of(ptr, type, member) ({                  \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) );})


# endif
