/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:29:24 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:17:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char *s;
	char *d;

	s = (char*)src;
	d = (char*)dest;
	while (n--)
	{
		*d = *s;
		if (n)
		{
			d++;
			s++;
		}
	}
	return (dest);
}
