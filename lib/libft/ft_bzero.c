/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csubires <csubires@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 12:24:51 by csubires          #+#    #+#             */
/*   Updated: 2024/04/22 15:04:15 by csubires         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	x;
	char	*tmp_s;

	x = 0;
	tmp_s = (char *)s;
	while (x < n)
	{
		tmp_s[x] = '\0';
		x++;
	}
}