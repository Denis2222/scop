/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:25:50 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 11:20:38 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	model_control_key(t_app *app, t_vec3f *way, int key, t_vec3f dir)
{
	if (glfwGetKey(app->window, key) == GLFW_PRESS)
	{
		if (glfwGetKey(app->window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			vec3f_add(way, &dir);
		else
			vec3f_add(way, vec3f_scale(&dir, -1.0f));
	}
}

void	model_control_translate(t_app *app, t_model *model)
{
	t_vec3f ve;

	vec3fedit(&ve, 0.0f, 0.0f, 0.0f);
	vec3fedit(&ve, 0.04f, 0.0f, 0.0f);
	model_control_key(app, model->position, GLFW_KEY_A, ve);
	vec3fedit(&ve, 0.0f, 0.04f, 0.0f);
	model_control_key(app, model->position, GLFW_KEY_S, ve);
	vec3fedit(&ve, 0.0f, 0.0f, 0.04f);
	model_control_key(app, model->position, GLFW_KEY_D, ve);
}

void	model_control_rotate(t_app *app, t_model *model)
{
	t_vec3f ve;

	vec3fedit(&ve, 0.0f, 0.0f, 0.0f);
	if (glfwGetKey(app->window, GLFW_KEY_J) == GLFW_PRESS)
	{
		vec3f_print(model->position);
		vec3f_print(model->rotation);
		vec3f_print(model->scale);
	}
	vec3fedit(&ve, 0.02f, 0.0f, 0.0f);
	model_control_key(app, model->rotation, GLFW_KEY_Q, ve);
	vec3fedit(&ve, 0.0f, 0.02f, 0.0f);
	model_control_key(app, model->rotation, GLFW_KEY_W, ve);
	vec3fedit(&ve, 0.0f, 0.0f, 0.02f);
	model_control_key(app, model->rotation, GLFW_KEY_E, ve);
}

void	model_control_scale(t_app *app, t_model *model)
{
	t_vec3f ve;

	vec3fedit(&ve, 0.0f, 0.0f, 0.0f);
	vec3fedit(&ve, -0.02f, 0.0f, 0.0f);
	model_control_key(app, model->scale, GLFW_KEY_Z, ve);
	vec3fedit(&ve, 0.0f, -0.02f, 0.0f);
	model_control_key(app, model->scale, GLFW_KEY_X, ve);
	vec3fedit(&ve, 0.0f, 0.0f, -0.02f);
	model_control_key(app, model->scale, GLFW_KEY_C, ve);
}

void	model_control(t_app *app, t_model *model)
{
	if (strcmp(model->obj_filename, "./assets/light/lantern.obj") == 0)
	{
		vec3f_cpy(model->position, app->input->lightPos);
		vec3f_move(model->position, 1.f, 1.f, 1.f);
		return ;
	}
	if (strcmp(model->obj_filename, "./assets/skybox/space.obj") == 0)
		return ;
	model_control_rotate(app, model);
	model_control_translate(app, model);
	model_control_scale(app, model);
	if (app->input->autoRotate)
		vec3f_move(model->rotation, 0.0f, 0.01f, 0.0f);
}
