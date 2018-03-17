/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 12:01:38 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	parse_face_8(t_tmp_obj *t)
{
	t->facefound = 1;
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[1], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[3], 1));
	if (t->temp_uv)
	{
		list_push(&t->uv_indices, list_new_uint(t->uv_index[0], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[1], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[2], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[0], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[2], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[3], 1));
	}
}

void	parse_face_8_6(FILE *file, t_tmp_obj *t)
{
	fseek(file, t->read_head, SEEK_SET);
	t->matches = fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n",
	&t->vertex_index[0], &t->uv_index[0],
	&t->vertex_index[1], &t->uv_index[1],
	&t->vertex_index[2], &t->uv_index[2],
	&t->vertex_index[3], &t->uv_index[3]);
	if (t->matches == 8)
	{
		parse_face_8(t);
	}
	if (t->matches == 6)
	{
		parse_face_6(t);
	}
}

void	parse_face_9(t_tmp_obj *t)
{
	t->facefound = 1;
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[1], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	if (t->temp_uv)
	{
		list_push(&t->uv_indices, list_new_uint(t->uv_index[0], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[1], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[2], 1));
	}
	if (t->temp_normal)
	{
		list_push(&t->normal_indices, list_new_uint(t->normal_index[0], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[1], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[2], 1));
	}
}

void	parse_face_12(t_tmp_obj *t)
{
	t->facefound = 1;
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[1], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	list_push(&t->vertex_indices, list_new_uint(t->vertex_index[3], 1));
	if (t->temp_uv)
	{
		list_push(&t->uv_indices, list_new_uint(t->uv_index[0], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[1], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[2], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[0], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[2], 1));
		list_push(&t->uv_indices, list_new_uint(t->uv_index[3], 1));
	}
	if (t->temp_normal)
	{
		list_push(&t->normal_indices, list_new_uint(t->normal_index[0], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[1], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[2], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[0], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[2], 1));
		list_push(&t->normal_indices, list_new_uint(t->normal_index[3], 1));
	}
}

int		parse_face(FILE *file, t_tmp_obj *t)
{
	t->facefound = 0;
	t->read_head = ftell(file);
	t->matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
	&t->vertex_index[0], &t->uv_index[0], &t->normal_index[0],
	&t->vertex_index[1], &t->uv_index[1], &t->normal_index[1],
	&t->vertex_index[2], &t->uv_index[2], &t->normal_index[2],
	&t->vertex_index[3], &t->uv_index[3], &t->normal_index[3]);
	if (t->matches == 9)
		parse_face_9(t);
	else if (t->matches == 12)
		parse_face_12(t);
	else
		parse_face_3_4(file, t);
	if (t->facefound == 0)
		parse_face_8_6(file, t);
	if (t->facefound == 0)
		printf("Unreadable face \n");
	return (1);
}
