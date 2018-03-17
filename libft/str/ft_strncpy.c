/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:31:16 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:42 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t pos;

	pos = 0;
	while (src[pos] != '\0' && pos < n)
	{
		dest[pos] = src[pos];
		pos++;
	}
	if (pos < n)
	{
		while (pos < n)
		{
			dest[pos] = '\0';
			pos++;
		}
	}
	return (dest);
}
