/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:30:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 17:12:52 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	camera_free(t_input *input)
{
	free(input->pos);
	free(input->dir);
	free(input->right);
	free(input->delta_dir);
	free(input->delta_right);
	free(input->light_pos);
	free(input);
}

t_input	*secure_malloc_input(void)
{
	t_input	*in;

	in = (t_input*)malloc(sizeof(t_input));
	if (!in)
	{
		printf("Malloc Error\n");
		exit(1);
	}
	return (in);
}

t_input	*camera_init(void)
{
	t_input	*in;

	in = secure_malloc_input();
	in->last_time = glfwGetTime();
	in->horizontal_angle = 7.2f;
	in->vertical_angle = 3.6f;
	in->initial_fov = BASE_FOV;
	in->speed = 10.0f;
	in->mouse_speed = 0.025f;
	in->pos = vec3f(10.0f, 3.0f, 3.0f);
	in->dir = vec3f(1.0f, 0.0f, 0.0f);
	in->right = vec3f(0.0f, 0.0f, 0.0f);
	in->delta_dir = vec3f(0.0f, 0.0f, 0.0f);
	in->delta_right = vec3f(0.0f, 0.0f, 0.0f);
	in->view = 0;
	in->light_pos = vec3f(4.0f, 4.0f, 4.0f);
	in->var = 0.0f;
	in->render_mode = GL_TRIANGLES;
	in->auto_rotate = 1;
	in->skybox = 0;
	in->ratio_color_bool = 1;
	in->ratio_color_texture = 1.0f;
	return (in);
}

void	camera_controls(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		vec3f_add(app->input->pos, app->input->delta_dir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		vec3f_sub(app->input->pos, app->input->delta_dir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		vec3f_add(app->input->pos, app->input->delta_right);
	}
	if (glfwGetKey(app->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		vec3f_sub(app->input->pos, app->input->delta_right);
	}
	controls_direction(app);
	control_view(app);
	control_render_mode(app);
	control_color_texture(app);
	control_auto_rotate(app);
	if (app->input->ratio_color_bool && app->input->ratio_color_texture <= 1)
		app->input->ratio_color_texture += 0.01;
	else if (app->input->ratio_color_texture >= 0)
		app->input->ratio_color_texture -= 0.01;
}
