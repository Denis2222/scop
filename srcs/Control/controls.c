/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 07:30:15 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 13:08:42 by dmoureu-         ###   ########.fr       */
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

void	control_render_mode(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_M) == GLFW_PRESS)
	{
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_M) == GLFW_RELEASE &&
			oldState == GLFW_PRESS)
		{
			app->input->renderMode++;
			app->input->renderMode = app->input->renderMode % 12;
		}
		oldState = glfwGetKey(app->window, GLFW_KEY_M);
	}
}

void	control_color_texture(t_app *app)
{
	if (glfwGetKey(app->window, GLFW_KEY_T) == GLFW_PRESS)
	{
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_T) == GLFW_RELEASE &&
		oldState == GLFW_PRESS)
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
		oldState = GLFW_PRESS;
		if (glfwGetKey(app->window, GLFW_KEY_K) == GLFW_RELEASE &&
			oldState == GLFW_PRESS)
		{
			app->input->autoRotate = app->input->autoRotate ? 0 : 1;
		}
	}
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
