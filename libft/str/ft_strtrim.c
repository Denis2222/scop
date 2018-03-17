/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 21:14:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:53 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		istrimable(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else
		return (0);
}

char			*ft_strtrim(char const *s)
{
	int				i;
	int				length;
	unsigned int	start;
	unsigned int	end;

	if (s == NULL)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	start = 0;
	end = length;
	while (i < length && istrimable(s[i]))
	{
		i++;
		start = i;
	}
	i = length - 1;
	while (i >= (int)start && istrimable(s[i]))
	{
		end = i;
		i--;
	}
	return (ft_strsub(s, start, end - start));
}

char			*ft_strtrimfree(char *s)
{
	char *str;

	str = ft_strtrim(s);
	ft_strdel(&s);
	return (str);
}
