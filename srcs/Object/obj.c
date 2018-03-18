/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/13 03:58:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/18 23:49:41 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	load_all_in_obj_normal(t_obj *obj_data, t_tmp_obj *t)
{
	if (obj_data->nnormals)
	{
		t->normal_i = t->ni->value;
		if (t->normal_i < 1)
			t->normal_i = list_length(t->temp_normal) + t->normal_i + 1;
		t->normal = list_get(t->temp_normal, t->normal_i - 1);
		if (t->normal == NULL)
			return ;
		obj_data->normals[t->n * 3 + 0] = t->normal->x;
		obj_data->normals[t->n * 3 + 1] = t->normal->y;
		obj_data->normals[t->n * 3 + 2] = t->normal->z;
	}
}

void	load_all_in_obj(t_obj *obj_data, t_tmp_obj *t)
{
	t->vertex_i = t->vi->value;
	if (t->vertex_i < 1)
		t->vertex_i = list_length(t->temp_vertex) + t->vertex_i + 1;
	t->vertex = list_get(t->temp_vertex, t->vertex_i - 1);
	if (t->vertex == NULL)
	{
		printf(" Parsing error: miss v : Deprecated mode \n");
		return ;
	}
	obj_data->vertices[t->n * 3 + 0] = t->vertex->x;
	obj_data->vertices[t->n * 3 + 1] = t->vertex->y;
	obj_data->vertices[t->n * 3 + 2] = t->vertex->z;
	if (obj_data->nuvs)
	{
		t->uv_i = t->ui->value;
		if (t->uv_i < 1)
			t->uv_i = list_length(t->temp_uv) + t->uv_i + 1;
		t->uv = list_get(t->temp_uv, t->uv_i - 1);
		if (t->uv == NULL)
			return ;
		obj_data->uvs[t->n * 2 + 0] = t->uv->x;
		obj_data->uvs[t->n * 2 + 1] = t->uv->y;
	}
	load_all_in_obj_normal(obj_data, t);
}

void	model_load_obj_bind_shortcut(t_model *model, t_obj *obj)
{
	if (obj->nuvs > 0)
	{
		model->enable_uv = 1;
		model->uv = (t_vec2f*)&model->obj_data->uvs[0];
		model->tangent = (t_vec3f*)&model->obj_data->tangents[0];
		model->bitangent = (t_vec3f*)&model->obj_data->bitangents[0];
	}
	else
	{
		model->enable_uv = 0;
		model->uv = NULL;
		model->tangent = NULL;
		model->bitangent = NULL;
	}
	if (model->obj_data->nnormals > 0)
	{
		model->enable_normal = 1;
		model->normal = (t_vec3f*)&model->obj_data->normals[0];
	}
	else
	{
		model->enable_normal = 0;
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
	t.vi = t.vertex_indices;
	t.ui = t.uv_indices;
	t.ni = t.normal_indices;
	obj_init(obj, &t);
	while (t.n < obj->nvertices)
	{
		if (t.vi == NULL)
			break ;
		load_all_in_obj(obj, &t);
		t.vi = t.vi->next;
		if (t.ui)
			t.ui = t.ui->next;
		if (t.ni)
			t.ni = t.ni->next;
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
	model->obj_data = obj;
	model->nvertices = obj->nvertices;
	model->vertex = (t_vec3f*)&obj->vertices[0];
	model->color = (t_vec3f*)&obj->colors[0];
	model->enable_uv = 0;
	model->enable_normal = 0;
	model_load_obj_bind_shortcut(model, obj);
	return (1);
}
