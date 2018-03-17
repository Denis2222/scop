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
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[3], 1));
	if (t->temp_uv)
	{
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[1], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[3], 1));
	}
}

void	parse_face_8_6(FILE *file, t_tmp_obj *t)
{
	fseek(file, t->readHead, SEEK_SET);
	t->matches = fscanf(file, "%d/%d %d/%d %d/%d %d/%d\n",
	&t->vertexIndex[0], &t->uvIndex[0],
	&t->vertexIndex[1], &t->uvIndex[1],
	&t->vertexIndex[2], &t->uvIndex[2],
	&t->vertexIndex[3], &t->uvIndex[3]);
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
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	if (t->temp_uv)
	{
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[1], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
	}
	if (t->temp_normal)
	{
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[0], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[1], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[2], 1));
	}
}

void	parse_face_12(t_tmp_obj *t)
{
	t->facefound = 1;
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[1], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[0], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[2], 1));
	list_push(&t->vertexIndices, list_new_uint(t->vertexIndex[3], 1));
	if (t->temp_uv)
	{
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[1], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[0], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[2], 1));
		list_push(&t->uvIndices, list_new_uint(t->uvIndex[3], 1));
	}
	if (t->temp_normal)
	{
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[0], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[1], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[2], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[0], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[2], 1));
		list_push(&t->normalIndices, list_new_uint(t->normalIndex[3], 1));
	}
}

int		parse_face(FILE *file, t_tmp_obj *t)
{
	t->facefound = 0;
	t->readHead = ftell(file);
	t->matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d\n",
	&t->vertexIndex[0], &t->uvIndex[0], &t->normalIndex[0],
	&t->vertexIndex[1], &t->uvIndex[1], &t->normalIndex[1],
	&t->vertexIndex[2], &t->uvIndex[2], &t->normalIndex[2],
	&t->vertexIndex[3], &t->uvIndex[3], &t->normalIndex[3]);
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
