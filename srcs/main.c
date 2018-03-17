/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:41:19 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:06:28 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	main_clean(t_app *app)
{
	camera_free(app->input);
	free(app->args->flags);
	free(app->args->files);
	free(app->args);
}

void	main_render(t_app *app)
{
	t_list	*models;
	int		i;

	while (glfwGetKey(app->window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
			glfwWindowShouldClose(app->window) == 0)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		camera_controls(app);
		i = 0;
		models = app->models;
		while (models)
		{
			model_render(app, models->addr);
			models = models->next;
			i++;
		}
		glfwSwapBuffers(app->window);
		glfwPollEvents();
	}
}

void	main_bind(t_app *app)
{
	t_list	*models;
	int		i;

	i = 0;
	load_meshes(app);
	models = app->models;
	while (models)
	{
		model_bind(models->addr);
		models = models->next;
		i++;
	}
}

void	main_load(t_app *app)
{
	load_bmp("./assets/poney.bmp");
	if (app->args->argc > 1 && app->args->argv[1])
		list_push(&app->models,
			list_new(model_new_scale(app->args->argv[1], 1.f, 1.f, 1.f),
			sizeof(t_model*)));
	else
		list_push(&app->models, list_new(model_new("./assets/42.obj"),
			sizeof(t_model*)));
	if (app->args->flags['l'])
		list_push(&app->models,
			list_new(model_new("./assets/light/lantern.obj"),
				sizeof(t_model*)));
	if (app->args->flags['s'])
		list_push(&app->models,
			list_new(model_new_scale("./assets/skybox/space.obj",
				10.0f, 10.0f, 10.0f), sizeof(t_model*)));
}

int		main(int argc, char **argv)
{
	t_app	*app;
	GLuint	vao;

	app = root();
	app->args = new_argvise(argc, argv);
	app->input = camera_init();
	if (!init_glfw(app))
	{
		printf("Failed to INIT GLFW\n");
		return (-1);
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	main_render(app);
	main_clean(app);
	glDeleteVertexArrays(1, &vao);
	glfwTerminate();
	return (0);
}
