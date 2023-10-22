/* ************************************************************************** */
/*                                                                            */
/*                                                    :::       :::     :::   */
/*   show_alloc_mem.c                                :+:       :+: :+: :+:    */
/*                                                 +:++:+     +:+  +  +:+     */
/*   By: amahla <ammah.connect@outlook.fr>       +#+  +:+    +#+     +#+      */
/*                                             +#+    +#+   +#+     +#+       */
/*   Created: 2023/10/22 03:04:37 by amahla  #+#      #+#  #+#     #+#        */
/*   Updated: 2023/10/22 04:09:39 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */


# include <malloc.h>


void	display_page(struct header_page *current_page, char *page_type);
void	ft_putnbr_base(uintptr_t ptr, char *base, size_t size);
void	display_chunk(struct header_chunk *current_chunk);


void	show_alloc_mem(void)
{
	char	*page_type[3] = {"TINY", "SMALL", "LARGE"};

	ft_putchar_fd('\n', 1);
	for (enum chunk_size_e type = TINY; type <= LARGE; type++)
		display_page(page[type], page_type[type]);
	ft_putchar_fd('\n', 1);
}


void	display_page(struct header_page *current_page, char *page_type)
{
	struct header_chunk	*current_chunk;

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
			current_chunk = current_chunk->next;
		}
		current_page = current_page->next;
	}
}


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


void	ft_putnbr_base(uintptr_t ptr, char *base, size_t size)
{
	if (size > 16)
		return;
	if (ptr >= size)
		ft_putnbr_base(ptr / size, base, size);
	write(1, base + ptr % size, 1);
}
