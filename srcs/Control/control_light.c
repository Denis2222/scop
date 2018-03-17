/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:43:32 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:13:39 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	light_controls2(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_KP_4) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x,
			app->input->light_pos->y, app->input->light_pos->z - 0.2f);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_7) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x,
			app->input->light_pos->y + 0.2f, app->input->light_pos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_1) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x,
			app->input->light_pos->y - 0.2f, app->input->light_pos->z);
	}
}

void	light_controls(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_KP_8) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x + 0.2f,
			app->input->light_pos->y, app->input->light_pos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_2) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x - 0.2f,
			app->input->light_pos->y, app->input->light_pos->z);
	}
	if (glfwGetKey(app->window, GLFW_KEY_KP_6) == GLFW_PRESS)
	{
		vec3fedit(app->input->light_pos, app->input->light_pos->x,
			app->input->light_pos->y, app->input->light_pos->z + 0.2f);
	}
	light_controls2(app);
}
