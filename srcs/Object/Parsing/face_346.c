/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   face_346.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:01:09 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 12:01:31 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	parse_face_3_4(FILE *file, t_tmp_obj *t)
{
	fseek(file, t->read_head, SEEK_SET);
	t->matches = fscanf(file, "%d %d %d %d\n",
		&t->vertex_index[0],
		&t->vertex_index[1],
		&t->vertex_index[2],
		&t->vertex_index[3]);
	if (t->matches == 3)
	{
		t->facefound = 1;
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[1], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
	}
	if (t->matches == 4)
	{
		t->facefound = 1;
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[1], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[0], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[2], 1));
		list_push(&t->vertex_indices, list_new_uint(t->vertex_index[3], 1));
	}
}

void	parse_face_6(t_tmp_obj *t)
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
}
