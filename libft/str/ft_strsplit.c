/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 13:14:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/15 19:55:40 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_strsplit_count(char const *s, char c)
{
	int	i;
	int	d;
	int	word;

	i = 0;
	d = 0;
	word = 0;
	while (s[i])
		if (s[i++] != c)
		{
			if (d == 0)
			{
				d = 1;
				word++;
			}
		}
		else
			d = 0;
	return (word);
}

static int		ft_strsplit_length(char const *s, char c, int cword)
{
	int	i;
	int	d;
	int	word;
	int	length;

	length = 0;
	i = 0;
	d = 0;
	word = 0;
	while (s[i])
		if (s[i++] != c)
		{
			if (d == 0)
			{
				d = 1;
				word++;
			}
			if (d == 1 && word == cword)
				length++;
		}
		else
			d = 0;
	return (length);
}

static int		ft_strsplit_start(char const *s, char c, int cword)
{
	int	i;
	int	d;
	int	word;
	int	length;

	length = 0;
	i = 0;
	d = 0;
	word = 0;
	while (s[i])
		if (s[i++] != c)
		{
			if (d == 0)
			{
				d = 1;
				word++;
				if (word == cword)
					return (i - 1);
			}
		}
		else
			d = 0;
	return (length);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		nbword;
	int		i;
	int		start;
	int		length;

	if (s == NULL)
		return (NULL);
	nbword = ft_strsplit_count(s, c);
	if (!(tab = malloc(sizeof(char*) * (nbword + 1))))
		return (NULL);
	i = 0;
	while (i < nbword)
	{
		start = ft_strsplit_start(s, c, i + 1);
		length = ft_strsplit_length(s, c, i + 1);
		tab[i] = ft_strsub(s, (unsigned int)start, (size_t)length);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
