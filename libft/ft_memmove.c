/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:45:40 by csubires          #+#    #+#             */
/*   Updated: 2024/04/23 14:40:45 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	x;

	if ((!dst && !src) || (dst == src))
		return (dst);
	if (src < dst)
		while (len--)
			((unsigned char *)dst)[len] = ((unsigned char *)src)[len];
	else
	{
		x = 0;
		while (x < len)
		{
			((unsigned char *)dst)[x] = ((unsigned char *)src)[x];
			x++;
		}
	}
	return (dst);
}
