/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 10:51:41 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <ctype.h>

int checkobj(FILE *file)
{
	char	header[100];
	int		read;
	int		i;

	read = fread(header, 1, 50, file);
	i = 0;
	while(i < read)
	{
		if(!isascii(header[i]))
		{
			printf("Caractere cheulou dans .obj ... \n");
			return (0);
		}
		i++;
	}
	return (1);
}

int		tmp_obj_init(t_tmp_obj *t, const char *path)
{
	t->temp_vertex = NULL;
	t->temp_uv = NULL;
	t->temp_normal = NULL;
	t->vertexIndices = NULL;
	t->uvIndices = NULL;
	t->normalIndices = NULL;
	t->mtl = NULL;
	t->n = 0;
	t->file = fopen(path, "r");
	t->path = strdup(path);
	if (t->file == NULL)
	{
		printf("Impossible to open the file !\n");
		return (0);
	}
	if (checkobj(t->file))
		return (1);
	return (0);
}

int		tmp_obj_loading(t_tmp_obj *t)
{
	t->res = fscanf(t->file, "%s", t->lineHeader);
	if (t->res == EOF)
		return (0);
	if (strcmp(t->lineHeader, "mtllib") == 0)
	{
		parse_mtl(t->file, t);
	} else if (strcmp(t->lineHeader, "v") == 0)
	{
		parse_v(t->file, t);
	}
	else if (strcmp(t->lineHeader, "vt") == 0)
	{
		parse_vt(t->file, t);
	}
	else if (strcmp(t->lineHeader, "vn") == 0)
	{
		parse_vn(t->file, t);
	}
	else if (strcmp(t->lineHeader, "f") == 0)
		parse_face(t->file, t);
	else
		fgets(t->stupidBuffer, 1000, t->file);
	return (1);
}

void 	tmp_obj_free_low(t_tmp_obj *t)
{
	list_del(&t->temp_vertex);
	list_del(&t->temp_uv);
	list_del(&t->temp_normal);
	list_del(&t->vI);
	list_del(&t->uI);
	list_del(&t->nI);
	list_del(&t->vertexIndices);
	list_del(&t->uvIndices);
	list_del(&t->normalIndices);
	free(t->path);
}

void 	tmp_obj_free(t_tmp_obj *t)
{
	t_list *l;

	l = t->temp_vertex;
	while (l)
	{
		if (l->size > 1)
			free(l->addr);
		l = l->next;
	}
	l = t->temp_uv;
	while (l)
	{
		if (l->size > 1)
			free(l->addr);
		l = l->next;
	}
	l = t->temp_normal;
	while (l)
	{
		if (l->size > 1)
			free(l->addr);
		l = l->next;
	}
	tmp_obj_free_low(t);
}
