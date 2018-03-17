/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:29:33 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:17:48 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	s = src;
	d = dst;
	if (d > s && (size_t)(d - s) <= len)
		while (len--)
			d[len] = s[len];
	else
	{
		i = 0;
		while (i != len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}
