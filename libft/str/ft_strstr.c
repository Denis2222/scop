/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:31:45 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, const char *to_find)
{
	int	pos;
	int x;

	if (ft_strlen((char *)to_find) == 0)
		return (str);
	pos = 0;
	x = 0;
	while (str[pos] != '\0')
	{
		if (str[pos] == to_find[x])
		{
			x++;
			if (to_find[x] == '\0')
				return (&str[pos - x + 1]);
		}
		else
		{
			pos = pos - x;
			x = 0;
		}
		pos++;
	}
	return (0);
}
