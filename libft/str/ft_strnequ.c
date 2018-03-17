/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:37:46 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:43 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (s1 == NULL && s2 == NULL)
		return (1);
	else if (s1 == NULL || s2 == NULL)
		return (0);
	if (ft_strncmp((char *)s1, (char *)s2, n) == 0)
		return (1);
	else
		return (0);
}
