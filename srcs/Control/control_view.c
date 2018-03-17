/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_view.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:15:04 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:17:01 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	controls_direction(t_app *app)
{
	float	delta_time;
	double	xpos;
	double	ypos;

	glfwGetCursorPos(app->window, &xpos, &ypos);
	delta_time = (glfwGetTime() - app->input->last_time);
	light_controls(app);
	app->input->last_time = glfwGetTime();
	glfwSetCursorPos(app->window, WIDTH / 2, HEIGHT / 2);
	app->input->horizontal_angle += app->input->mouse_speed * delta_time *
	(float)(WIDTH / 2 - xpos);
	app->input->vertical_angle += app->input->mouse_speed * delta_time *
	(float)(HEIGHT / 2 - ypos);
	vec3fedit(app->input->dir, cos(app->input->vertical_angle) *
	sin(app->input->horizontal_angle), sin(app->input->vertical_angle),
	cos(app->input->vertical_angle) * cos(app->input->horizontal_angle));
	vec3fedit(app->input->right, sin(app->input->horizontal_angle - 3.14f /
	2.0f), 0, cos(app->input->horizontal_angle - 3.14f / 2.0f));
	vec3fedit(app->input->delta_dir, app->input->dir->x * delta_time *
	app->input->speed, app->input->dir->y * delta_time * app->input->speed,
	app->input->dir->z * delta_time * app->input->speed);
	vec3fedit(app->input->delta_right, app->input->right->x * delta_time *
	app->input->speed, app->input->right->y * delta_time * app->input->speed,
	app->input->right->z * delta_time * app->input->speed);
}

void	control_view(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_V) == GLFW_PRESS)
	{
		g_oldstate = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_V) == GLFW_RELEASE &&
			g_oldstate == GLFW_PRESS)
		{
			if (app->input->view == 0)
				app->input->view = 1;
			else
				app->input->view = 0;
		}
		g_oldstate = glfwGetKey(app->window, GLFW_KEY_V);
	}
}
