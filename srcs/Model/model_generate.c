/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_generate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 10:58:57 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:02:59 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_generate_uniform_model_rotation(t_model *model)
{
	t_mat4f	*rotate;
	t_mat4f	*identity;
	t_mat4f	*rotatex;
	t_mat4f	*rotatey;
	t_mat4f	*rotatez;

	rotatex = mat4f_rotate_x(mat4f_identity(1.0f), model->rotation->x);
	rotatey = mat4f_rotate_y(mat4f_identity(1.0f), model->rotation->y);
	rotatez = mat4f_rotate_z(mat4f_identity(1.0f), model->rotation->z);
	identity = mat4f_multiply(rotatex, rotatey);
	rotate = mat4f_multiply(identity, rotatez);
	glUniformMatrix4fv(model->ModelRotateID, 1, GL_FALSE, &rotate->m[0][0]);
	free(rotate);
	free(identity);
	free(rotatex);
	free(rotatey);
	free(rotatez);
}

void	model_generate_uniform_model(t_model *model)
{
	t_mat4f *translate;
	t_mat4f *scale;

	translate = mat4f_translate(model->position);
	scale = mat4f_scale(model->scale->x, model->scale->y, model->scale->z);
	glUniformMatrix4fv(model->ModelTranslateID, 1,
		GL_FALSE, &translate->m[0][0]);
	glUniformMatrix4fv(model->ModelScaleID, 1, GL_FALSE, &scale->m[0][0]);
	model_generate_uniform_model_rotation(model);
	free(translate);
	free(scale);
}

void	model_generate_uniform_projection(t_app *app, t_model *model)
{
	t_mat4f *projection;

	projection = mat4f_perspective(app->input->initialFoV,
		16.0f / 9.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(model->MatrixProjectionID, 1,
		GL_FALSE, &projection->m[0][0]);
	free(projection);
}

void	model_generate_uniform_view(t_app *app, t_model *model)
{
	t_mat4f *view;
	t_vec3f *target;
	t_vec3f *upvector;

	if (app->input->view)
		target = vec3f_new_add(app->input->pos, app->input->dir);
	else
		target = vec3f(.0f, .0f, .0f);
	upvector = vec3f(0.0f, 1.0f, 0.0f);
	view = mat4fLookAt(
		app->input->pos,
		target,
		upvector);
	glUniformMatrix4fv(model->MatrixViewID, 1, GL_FALSE, &view->m[0][0]);
	free(target);
	free(upvector);
	free(view);
}
