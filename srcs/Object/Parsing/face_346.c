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
	fseek(file, t->readHead, SEEK_SET);
	t->matches = fscanf(file, "%d %d %d %d\n",
		&t->vertexIndex[0],
		&t->vertexIndex[1],
		&t->vertexIndex[2],
		&t->vertexIndex[3]);
	if (t->matches == 3)
	{
		t->facefound = 1;
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	}
	if (t->matches == 4)
	{
		t->facefound = 1;
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
		list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[3], 1));
	}
}

void	parse_face_6(t_tmp_obj *t)
{
	t->facefound = 1;
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	if (t->temp_uv)
	{
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[1], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
	}
}
