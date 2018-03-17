/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 11:20:49 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 17:08:53 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

t_model	*model_new(char *objfile)
{
	t_model *model;

	model = (t_model*)malloc(sizeof(t_model));
	model->position = vec3f(0.0f, 0.0f, 0.0f);
	model->rotation = vec3f(0.0f, 0.0f, 0.0f);
	model->scale = vec3f(1.0f, 1.0f, 1.0f);
	model->obj_filename = strdup(objfile);
	model->loaded = 0;
	model->enable = 1;
	return (model);
}

t_model	*model_new_scale(char *objfile, float x, float y, float z)
{
	t_model	*model;

	model = (t_model*)malloc(sizeof(t_model));
	model->position = vec3f(0.0f, 0.0f, 0.0f);
	model->rotation = vec3f(0.0f, 0.0f, 0.0f);
	model->scale = vec3f(x, y, z);
	model->obj_filename = strdup(objfile);
	model->loaded = 0;
	model->enable = 1;
	return (model);
}

int		model_load(t_model *model)
{
	if (model_load_obj(model, model->obj_filename))
		model->loaded = 1;
	return (1);
}

void	model_render_send(t_app *app, t_model *model)
{
	model_send_mvp(app, model);
	model_send_texture(0, model->diffuse_texture, model->diffuse_texture_id);
	model_send_texture(1, model->specular_texture, model->specular_texture_id);
	model_send_texture(2, model->normal_texture, model->normal_texture_id);
	glUniform1f(model->ratio_colortexture_id, app->input->ratio_color_texture);
	glUniform3f(model->light_id, app->input->light_pos->x,
		app->input->light_pos->y, app->input->light_pos->z);
}

int		model_render(t_app *app, t_model *model)
{
	unsigned int vertex_attrib;
	unsigned int attr;

	vertex_attrib = 0;
	attr = 0;
	if (!(model->loaded && model->enable))
		return (0);
	model_control(app, model);
	glUseProgram(model->program_id);
	model_render_send(app, model);
	model_send_buffer(vertex_attrib++, &model->vertexbuffer, 3);
	model_send_buffer(vertex_attrib++, &model->colorbuffer, 3);
	if (model->enable_uv)
		model_send_buffer(vertex_attrib++, &model->uvbuffer, 2);
	if (model->enable_normal)
		model_send_buffer(vertex_attrib++, &model->normalbuffer, 3);
	if (model->enable_uv)
	{
		model_send_buffer(vertex_attrib++, &model->tangentbuffer, 3);
		model_send_buffer(vertex_attrib++, &model->bitangentbuffer, 3);
	}
	glDrawArrays(app->input->render_mode, 0, model->nvertices);
	while (attr < vertex_attrib)
		glDisableVertexAttribArray(attr++);
	return (1);
}
