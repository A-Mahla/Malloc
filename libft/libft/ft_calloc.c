/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                     :+:       :+: :+: :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: amahla <amahla@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 12:27:43 by amahla            #+#    #+#             */
/*   Updated: 2023/10/22 13:40:42 by amahla ###       ########     ########   */
/*                                                                            */
/* ************************************************************************** */

# include"libft.h"
# include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dst;
	size_t	i;

	i = 0;
	if (nmemb > SIZE_MAX / size)
		return NULL;
	else
		dst = malloc(nmemb * size);
	if (!dst)
		return (NULL);
	while (i < nmemb * size)
		*((unsigned char *)dst + i++) = 0;
	return (dst);
}
