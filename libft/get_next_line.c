/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/05 22:00:08 by dmoureu-          #+#    #+#             */
/*   Updated: 2016/04/23 03:18:03 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*strchrsubdup(char **str)
{
	char	*rest;
	char	*ret;

	rest = ft_strdup(ft_strchr(*str, '\n'));
	ret = ft_strsub(*str, 0, ft_strlen(*str) - ft_strlen(rest));
	free(*str);
	*str = ft_strsub(rest, 1, ft_strlen(rest));
	free(rest);
	return (ret);
}

static int	find_next(char *str)
{
	if (str)
		if (ft_strchr(str, '\n'))
			return (1);
	return (0);
}

static char	*ft_strjoin_free(char *s1, char *s2)
{
	char *tmp;

	tmp = ft_strdup(s1);
	free(s1);
	s1 = ft_strjoin(tmp, s2);
	free(tmp);
	return (s1);
}

static int	store_read(t_file *file, char **line, char *buf)
{
	int		e;

	if (!find_next(file->buf))
	{
		while (!find_next(file->buf) &&
				(e = read(file->fd, buf, BUFF_SIZE)) >= 1)
		{
			file->buf = ft_strjoin_free(file->buf, buf);
			ft_bzero(buf, BUFF_SIZE);
		}
		if (e < 0)
			return (-1);
		if (e == 0 && !find_next(file->buf) && ft_strlen(file->buf))
		{
			*line = ft_strdup(file->buf);
			ft_strclr(file->buf);
			return (1);
		}
		if (!ft_strlen(file->buf) && e == 0)
			return (0);
	}
	*line = strchrsubdup(&file->buf);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_list	*files = 0;
	t_list			*list;
	t_file			*file;
	char			*buf;
	int				ret;

	list = files;
	while (list && ((t_file*)list->content)->fd != fd)
		list = list->next;
	if (!list)
	{
		file = (t_file*)malloc(sizeof(t_file));
		file->fd = fd;
		file->buf = ft_strnew(BUFF_SIZE + 1);
		list = ft_lstnew(file, sizeof(t_file));
		ft_lstadd(&files, list);
	}
	buf = ft_strnew(BUFF_SIZE + 1);
	ret = store_read(list->content, line, buf);
	free(buf);
	return (ret);
}
