/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argvise.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/01 03:17:40 by dmoureu-          #+#    #+#             */
/*   Updated: 2017/04/01 05:57:36 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**argvisefiles(t_argvise *a)
{
	while (a->i < a->argc)
	{
		if (a->argv[a->i][0] != '-')
		{
			a->files[a->nfiles++] = a->argv[a->i++];
			continue;
		}
		a->j = 1;
		while (a->argv[a->i][a->j] != '\0')
		{
			if (!ft_strcmp(a->argv[a->i], "--"))
			{
				a->i++;
				while (a->i < a->argc)
					a->files[a->nfiles++] = a->argv[a->i++];
				break ;
			}
			else
				a->flags[(int)a->argv[a->i][a->j++]] = 1;
		}
		a->i++;
	}
	a->files[a->nfiles] = 0;
	return (a->files);
}

char		*argviseflags(t_argvise *a)
{
	while (a->i < a->argc)
	{
		if (a->argv[a->i][0] != '-')
		{
			a->files[a->nfiles++] = a->argv[a->i++];
			continue;
		}
		a->j = 1;
		while (a->argv[a->i][a->j] != '\0')
		{
			if (!ft_strcmp(a->argv[a->i], "--"))
			{
				a->i++;
				while (a->i < a->argc)
					a->files[a->nfiles++] = a->argv[a->i++];
				break ;
			}
			else
				a->flags[(int)a->argv[a->i][a->j++]] = 1;
		}
		a->i++;
	}
	a->files[a->nfiles] = 0;
	return (a->flags);
}

t_argvise	*new_argvise(int argc, char **argv)
{
	t_argvise *a;

	a = (t_argvise*)malloc(sizeof(t_argvise));
	a->argc = argc;
	a->argv = argv;
	a->nfiles = 0;
	a->i = 1;
	a->j = 1;
	a->files = malloc(sizeof(char*) * (argc + 1));
	a->flags = ft_strnew(256);
	a->files = argvisefiles(a);
	a->flags = argviseflags(a);
	return (a);
}
