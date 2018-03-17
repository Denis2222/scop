/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrepchrbystr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/23 04:47:42 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/05/22 09:16:49 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_replacechrbystrfusion(char *out, char *tmp)
{
	char	*tmp2;

	if (ft_strlen(out) > 0)
	{
		tmp2 = out;
		out = ft_strjoin(out, " ");
		free(tmp2);
	}
	tmp2 = out;
	out = ft_strjoin(out, tmp);
	ft_strdel(&tmp2);
	ft_strdel(&tmp);
	return (out);
}

static char	*ft_repchrbystrwhile(char **split, char *pwd, char old)
{
	char	*tmp;
	int		i;
	char	*out;

	i = 0;
	out = ft_strdup("");
	while (split[i])
	{
		if (split[i][0] == old)
		{
			if (ft_strlen(split[i]) > 1)
				tmp = ft_strjoin(pwd, &split[i][1]);
			else
				tmp = ft_strdup(pwd);
		}
		else
			tmp = ft_strdup(split[i]);
		out = ft_replacechrbystrfusion(out, tmp);
		i++;
	}
	return (out);
}

char		*ft_strrepchrbystr(char *str, char c, char *rep)
{
	char	**split;
	char	*out;

	if (str[0] == c)
	{
		if (str[1])
			out = ft_strjoin(rep, &str[1]);
		else
			out = rep;
		return (out);
	}
	split = ft_strsplit(str, ' ');
	out = ft_repchrbystrwhile(split, rep, c);
	ft_tabfree(split);
	return (out);
}
