/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   show_alloc_mem.c                                :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/22 03:04:37 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 21:39:50 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include <malloc.h>


void	display_page(struct header_page *current_page, char *page_type);
void	ft_putnbr_base(uintptr_t ptr, char *base, size_t size);
void	display_chunk(struct header_chunk *current_chunk);


/*
 * @function show_alloc_mem()
 *
 * @brief display memory used by the program
 *
 * @return void
 *
 */

void	show_alloc_mem(void)
{
	char	*page_type[3] = {"TINY", "SMALL", "LARGE"};

	ft_putchar_fd('\n', 1);
	pthread_mutex_lock(&multi_threading);
	for (enum chunk_size_e type = TINY; type <= LARGE; type++)
		display_page(page[type], page_type[type]);
	pthread_mutex_unlock(&multi_threading);
	ft_putchar_fd('\n', 1);
}


/*
 * @function display_page()
 *
 * @brief display memory pages.
 *
 * @return void
 *
 */

void	display_page(struct header_page *current_page, char *page_type)
{
	struct header_chunk	*current_chunk;

	if (current_page && !current_page->nb_allocated_chunk)
		return;
	while (current_page) {
		ft_putstr_fd(page_type, 1);
		ft_putstr_fd(" : 0x", 1);
		ft_putnbr_base((uintptr_t)current_page, "0123456789ABCDEF", 16);
		ft_putchar_fd('\n', 1);
		current_chunk = (struct header_chunk *)((uint8_t *)current_page
				+ HEADER_PAGE_SIZE);
		while (current_chunk) {
			if (current_chunk->size & 1)
				display_chunk(current_chunk);
//			else								// to check free chunk
//				display_chunk(current_chunk);
			current_chunk = current_chunk->next;
		}
		current_page = current_page->next;
	}
}


/*
 * @function display_chunk()
 *
 * @brief display memory chunks.
 *
 * @return void
 *
 */

void	display_chunk(struct header_chunk *current_chunk)
{
	uintptr_t	end;
	uintptr_t	begin;

	end = (uintptr_t)((uint8_t *)current_chunk + (current_chunk->size & ~1L));
	begin = (uintptr_t)((uint8_t *)current_chunk + HEADER_CHUNK_SIZE);
	ft_putstr_fd("0x", 1);
	ft_putnbr_base(begin, "0123456789ABCDEF", 16);
	ft_putstr_fd(" - ", 1);
	ft_putstr_fd("0x", 1);
	ft_putnbr_base(end, "0123456789ABCDEF", 16);
	ft_putstr_fd(" : ", 1);
	ft_putnbr_base(end - begin, "0123456789ABCDEF", 10);
	ft_putchar_fd('\n', 1);
}


/*
 * @function ft_putnbr_base()
 *
 * @brief display number (uintptr_t ptr) in a base given as argument (char *base),
 *        which has a size given as argument (size_t size).
 *
 * @return void
 *
 */

void	ft_putnbr_base(uintptr_t ptr, char *base, size_t size)
{
	if (size > 16)
		return;
	if (ptr >= size)
		ft_putnbr_base(ptr / size, base, size);
	write(1, base + ptr % size, 1);
}
