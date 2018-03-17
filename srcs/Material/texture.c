/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 09:02:59 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 10:56:34 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void		add_texture(char *path, unsigned char *data, int width, int height)
{
	t_texture	*t;
	t_app		*app;

	printf("		%s\n", path);
	t = (t_texture*)malloc(sizeof(t_texture));
	if (!t)
	{
		printf("Erreur malloc add texture ! \n");
		exit(1);
	}
	t->path = strdup(path);
	t->data = data;
	t->width = width;
	t->height = height;
	t->textureID = 0;
	t->loaded = 0;
	app = root();
	list_push(&app->textures, list_new(t, sizeof(t_texture*)));
}

t_texture	*get_texture(char *path)
{
	t_list		*l;
	t_texture	*t;
	t_app		*app;

	app = root();
	l = app->textures;
	while (l)
	{
		t = l->addr;
		if (strcmp(path, t->path) == 0)
			return (t);
		l = l->next;
	}
	return (NULL);
}

char		*concat_filepath(char *folder, char **path)
{
	char	*dir;
	char	*filepath;

	dir = ft_dirname(folder);
	filepath = (char *)malloc((strlen(dir) + strlen(*path) + 5) * sizeof(char));
	bzero(filepath, (strlen(dir) + strlen(*path) + 5));
	filepath = strcat(filepath, dir);
	filepath = strcat(filepath, "/");
	filepath = strcat(filepath, *path);
	free(dir);
	return (filepath);
}

void		get_path_for_texture(char *folder, char **path)
{
	char	*filepath;
	FILE	*file;

	file = fopen(*path, "r");
	if (file == NULL)
	{
		filepath = concat_filepath(folder, path);
		file = fopen(filepath, "r");
		free(*path);
		*path = filepath;
		if (file == NULL)
		{
			printf("Impossible to open texture file : %s !\n", filepath);
			return ;
		}
		fclose(file);
	}
	fclose(file);
	return ;
}

char		*load_texture(char *path, t_tmp_obj *t)
{
	get_path_for_texture(t->path, &path);
	if (get_texture(path))
	{
		printf("Texture Already load ! ");
		return (path);
	}
	if (!(load_bmp(path)))
	{
		printf("Texture %s  Not Found  Or not correct Format !\n", path);
		return (path);
	}
	return (path);
}
