/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:31:34 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:46 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	l;

	l = ft_strlen((char *)s);
	while (s[l] != (char)c && l >= 0)
		l--;
	if (s[l] == (char)c)
		return ((char *)&s[l]);
	return (NULL);
}
