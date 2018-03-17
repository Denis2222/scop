/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   root.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:26:45 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:06:23 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_app	*root(void)
{
	static t_app	*app = 0;

	if (app == 0)
	{
		app = (t_app*)malloc(sizeof(t_app));
		if (!app)
		{
			printf("General malloc fail root \n");
			exit(1);
		}
		app->models = NULL;
		app->textures = NULL;
		app->objs = NULL;
		app->shaders = NULL;
	}
	return (app);
}

char	*ft_dirname(const char *filepath)
{
	char	*result;
	char	**tab;
	int		nb;
	int		i;

	result = ft_strnew(strlen(filepath));
	tab = ft_strsplit(filepath, '/');
	nb = ft_tablen(tab);
	i = 0;
	while (i < nb - 1)
	{
		if (tab[i])
		{
			strcat(result, tab[i]);
			strcat(result, "/");
		}
		i++;
	}
	ft_tabfree(tab);
	return (result);
}
