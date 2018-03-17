/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 11:31:40 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_cswap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

char		*ft_strrev(char *str)
{
	int length;
	int start;
	int end;

	start = 0;
	length = ft_strlen(str);
	end = length - 1;
	while (start < end)
	{
		ft_cswap(&str[start], &str[end]);
		start++;
		end--;
	}
	return (str);
}
