/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:35:11 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	parse_v(FILE *file, t_tmp_obj *t)
{
	t->vertex = vec3f(0.0f, 0.0f, 0.0f);
	fscanf(file, "%f %f %f \n", &t->vertex->x, &t->vertex->y, &t->vertex->z);
	list_push(&t->temp_vertex, list_new(t->vertex, 3));
}

void	parse_vt(FILE *file, t_tmp_obj *t)
{
	t->uv = vec2f(0.0f, 0.0f);
	fscanf(file, "%f %f\n", &t->uv->x, &t->uv->y);
	list_push(&t->temp_uv, list_new(t->uv, 2));
}

void	parse_vn(FILE *file, t_tmp_obj *t)
{
	t->normal = vec3f(0.0f, 0.0f, 0.0f);
	fscanf(file, "%f %f %f \n", &t->normal->x, &t->normal->y, &t->normal->z);
	list_push(&t->temp_normal, list_new(t->normal, 3));
}

void	parse_mtl(FILE *file, t_tmp_obj *t)
{
	char mtlpath[1024];

	fscanf(file, "%s \n", mtlpath);
	printf("	%s\n", mtlpath);
	t->mtl = new_mtl(mtlpath, t);
}
