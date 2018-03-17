/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:15:56 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:16:57 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	control_render_mode(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_M) == GLFW_PRESS)
	{
		g_oldstate = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_M) == GLFW_RELEASE &&
			g_oldstate == GLFW_PRESS)
		{
			app->input->renderMode++;
			app->input->renderMode = app->input->renderMode % 12;
		}
		g_oldstate = glfwGetKey(app->window, GLFW_KEY_M);
	}
}

void	control_color_texture(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_T) == GLFW_PRESS)
	{
		g_oldstate = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_T) == GLFW_RELEASE &&
		g_oldstate == GLFW_PRESS)
		{
			app->input->RatioColorTextureBool =
				app->input->RatioColorTextureBool ? 0 : 1;
		}
	}
}

void	control_auto_rotate(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_K) == GLFW_PRESS)
	{
		g_oldstate = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_K) == GLFW_RELEASE &&
			g_oldstate == GLFW_PRESS)
		{
			app->input->autoRotate = app->input->autoRotate ? 0 : 1;
		}
	}
}
