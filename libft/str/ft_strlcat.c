/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:30:41 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:12 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	int	size_dest;
	int	size_src;

	size_dest = ft_strlen(dest);
	size_src = ft_strlen(src);
	dest = ft_strncat(dest, src, (size - size_dest - 1));
	if (size >= (size_t)(size_dest + size_src))
		return (size_dest + size_src);
	else if (size_dest == 0)
		return (size_src);
	else
		return (size + size_src);
}
