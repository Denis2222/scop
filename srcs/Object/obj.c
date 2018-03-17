/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:09:28 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	load_all_in_obj_normal(t_obj *obj_data, t_tmp_obj *t)
{
	if (obj_data->nnormals)
	{
		t->normalI = t->nI->value;
		if (t->normalI < 1)
			t->normalI = list_length(t->temp_normal) + t->normalI + 1;
		t->normal = list_get(t->temp_normal, t->normalI - 1);
		obj_data->normals[t->n * 3 + 0] = t->normal->x;
		obj_data->normals[t->n * 3 + 1] = t->normal->y;
		obj_data->normals[t->n * 3 + 2] = t->normal->z;
	}
}

void	load_all_in_obj(t_obj *obj_data, t_tmp_obj *t)
{
	t->vertexI = t->vI->value;
	if (t->vertexI < 1)
		t->vertexI = list_length(t->temp_vertex) + t->vertexI + 1;
	t->vertex = list_get(t->temp_vertex, t->vertexI - 1);
	obj_data->vertices[t->n * 3 + 0] = t->vertex->x;
	obj_data->vertices[t->n * 3 + 1] = t->vertex->y;
	obj_data->vertices[t->n * 3 + 2] = t->vertex->z;
	if (obj_data->nuvs)
	{
		t->uvI = t->uI->value;
		if (t->uvI < 1)
			t->uvI = list_length(t->temp_uv) + t->uvI + 1;
		t->uv = list_get(t->temp_uv, t->uvI - 1);
		obj_data->uvs[t->n * 2 + 0] = t->uv->x;
		obj_data->uvs[t->n * 2 + 1] = t->uv->y;
	}
	load_all_in_obj_normal(obj_data, t);
}

void	model_load_obj_bind_shortcut(t_model *model, t_obj *obj)
{
	if (obj->nuvs > 0)
	{
		model->enableUV = 1;
		model->uv = (t_vec2f*)&model->objData->uvs[0];
		model->tangent = (t_vec3f*)&model->objData->tangents[0];
		model->bitangent = (t_vec3f*)&model->objData->bitangents[0];
	}
	else
	{
		model->enableUV = 0;
		model->uv = NULL;
		model->tangent = NULL;
		model->bitangent = NULL;
	}
	if (model->objData->nnormals > 0)
	{
		model->enableNormal = 1;
		model->normal = (t_vec3f*)&model->objData->normals[0];
	}
	else
	{
		model->enableNormal = 0;
		model->normal = NULL;
	}
}

int		model_load_obj_processing(t_obj *obj, const char *path)
{
	t_tmp_obj	t;

	if (!tmp_obj_init(&t, path))
		return (0);
	while (tmp_obj_loading(&t))
		;
	t.vI = t.vertexIndices;
	t.uI = t.uvIndices;
	t.nI = t.normalIndices;
	obj_init(obj, &t);
	while (t.n < obj->nvertices)
	{
		if (t.vI == NULL)
			break ;
		load_all_in_obj(obj, &t);
		t.vI = t.vI->next;
		if (t.uI)
			t.uI = t.uI->next;
		if (t.nI)
			t.nI = t.nI->next;
		t.n++;
	}
	obj->mtl = t.mtl;
	tmp_obj_free(&t);
	return (1);
}

int		model_load_obj(t_model *model, const char *path)
{
	t_obj		*obj;

	if (!(obj = get_mesh(path)))
	{
		printf("Model loading... %s\n", model->obj_filename);
		obj = secure_malloc_obj();
		if (!model_load_obj_processing(obj, path))
			return (0);
		centerobj(obj);
		if (obj->nvertices > 0 && obj->nuvs > 0 && obj->nvertices == obj->nuvs)
			compute_tangent(obj);
		add_mesh(obj, path);
	}
	model->objData = obj;
	model->nvertices = obj->nvertices;
	model->vertex = (t_vec3f*)&obj->vertices[0];
	model->color = (t_vec3f*)&obj->colors[0];
	model->enableUV = 0;
	model->enableNormal = 0;
	model_load_obj_bind_shortcut(model, obj);
	return (1);
}
