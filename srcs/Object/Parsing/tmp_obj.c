/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/18 23:32:21 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>
#include <ctype.h>

int		checkobj(FILE *file)
{
	char	header[100];
	int		read;
	int		i;

	read = fread(header, 1, 50, file);
	i = 0;
	while (i < read)
	{
		if (!isascii(header[i]))
		{
			printf("Caractere cheulou dans .obj ... \n");
			return (0);
		}
		i++;
	}
	fseek(file, 0, SEEK_SET);
	return (1);
}

int		tmp_obj_init(t_tmp_obj *t, const char *path)
{
	t->temp_vertex = NULL;
	t->temp_uv = NULL;
	t->temp_normal = NULL;
	t->vertex_indices = NULL;
	t->uv_indices = NULL;
	t->normal_indices = NULL;
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
	t->res = fscanf(t->file, "%s", t->line_header);
	if (t->res == EOF)
		return (0);
	if (strcmp(t->line_header, "mtllib") == 0)
	{
		parse_mtl(t->file, t);
	}
	else if (strcmp(t->line_header, "v") == 0)
	{
		parse_v(t->file, t);
	}
	else if (strcmp(t->line_header, "vt") == 0)
	{
		parse_vt(t->file, t);
	}
	else if (strcmp(t->line_header, "vn") == 0)
	{
		parse_vn(t->file, t);
	}
	else if (strcmp(t->line_header, "f") == 0)
		parse_face(t->file, t);
	else
		fgets(t->stupid_buffer, 1000, t->file);
	return (1);
}

void	tmp_obj_free_low(t_tmp_obj *t)
{
	list_del(&t->temp_vertex);
	list_del(&t->temp_uv);
	list_del(&t->temp_normal);
	list_del(&t->vi);
	list_del(&t->ui);
	list_del(&t->ni);
	list_del(&t->vertex_indices);
	list_del(&t->uv_indices);
	list_del(&t->normal_indices);
	free(t->path);
}

void	tmp_obj_free(t_tmp_obj *t)
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
