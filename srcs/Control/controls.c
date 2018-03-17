/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:30:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:21:44 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	camera_free(t_input *input)
{
	free(input->pos);
	free(input->dir);
	free(input->right);
	free(input->deltaDir);
	free(input->deltaRight);
	free(input->lightPos);
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
	in->lastTime = glfwGetTime();
	in->horizontalAngle = 7.2f;
	in->verticalAngle = 3.6f;
	in->initialFoV = BASE_FOV;
	in->speed = 10.0f;
	in->mouseSpeed = 0.025f;
	in->pos = vec3f(10.0f, 3.0f, 3.0f);
	in->dir = vec3f(1.0f, 0.0f, 0.0f);
	in->right = vec3f(0.0f, 0.0f, 0.0f);
	in->deltaDir = vec3f(0.0f, 0.0f, 0.0f);
	in->deltaRight = vec3f(0.0f, 0.0f, 0.0f);
	in->view = 0;
	in->lightPos = vec3f(4.0f, 4.0f, 4.0f);
	in->var = 0.0f;
	in->renderMode = GL_TRIANGLES;
	in->autoRotate = 1;
	in->skybox = 0;
	in->RatioColorTextureBool = 1;
	in->RatioColorTexture = 1.0f;
	return (in);
}

void	camera_controls(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		vec3f_add(app->input->pos, app->input->deltaDir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		vec3f_sub(app->input->pos, app->input->deltaDir);
	}
	if (glfwGetKey(app->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		vec3f_add(app->input->pos, app->input->deltaRight);
	}
	if (glfwGetKey(app->window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		vec3f_sub(app->input->pos, app->input->deltaRight);
	}
	controls_direction(app);
	control_view(app);
	control_render_mode(app);
	control_color_texture(app);
	control_auto_rotate(app);
	if (app->input->RatioColorTextureBool && app->input->RatioColorTexture <= 1)
		app->input->RatioColorTexture += 0.01;
	else if (app->input->RatioColorTexture >= 0)
		app->input->RatioColorTexture -= 0.01;
}
