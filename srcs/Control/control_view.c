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
	delta_time = (glfwGetTime() - app->input->lastTime);
	light_controls(app);
	app->input->lastTime = glfwGetTime();
	glfwSetCursorPos(app->window, WIDTH / 2, HEIGHT / 2);
	app->input->horizontalAngle += app->input->mouseSpeed * delta_time *
	(float)(WIDTH / 2 - xpos);
	app->input->verticalAngle += app->input->mouseSpeed * delta_time *
	(float)(HEIGHT / 2 - ypos);
	vec3fedit(app->input->dir, cos(app->input->verticalAngle) *
	sin(app->input->horizontalAngle), sin(app->input->verticalAngle),
	cos(app->input->verticalAngle) * cos(app->input->horizontalAngle));
	vec3fedit(app->input->right, sin(app->input->horizontalAngle - 3.14f /
	2.0f), 0, cos(app->input->horizontalAngle - 3.14f / 2.0f));
	vec3fedit(app->input->deltaDir, app->input->dir->x * delta_time *
	app->input->speed, app->input->dir->y * delta_time * app->input->speed,
	app->input->dir->z * delta_time * app->input->speed);
	vec3fedit(app->input->deltaRight, app->input->right->x * delta_time *
	app->input->speed, app->input->right->y * delta_time * app->input->speed,
	app->input->right->z * delta_time * app->input->speed);
}

void	control_view(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_V) == GLFW_PRESS)
	{
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_V) == GLFW_RELEASE &&
			oldState == GLFW_PRESS)
		{
			if (app->input->view == 0)
				app->input->view = 1;
			else
				app->input->view = 0;
		}
		oldState = glfwGetKey(app->window, GLFW_KEY_V);
	}
}
