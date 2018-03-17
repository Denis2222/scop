/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:34:47 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:05:47 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	add_mesh(t_obj *obj, const char *path)
{
	t_app *app;

	app = root();
	obj->path = strdup(path);
	list_push(&app->objs, list_new(obj, sizeof(t_obj*)));
}

t_obj	*get_mesh(const char *path)
{
	t_app	*app;
	t_list	*l;
	t_obj	*obj;

	app = root();
	l = app->objs;
	while (l)
	{
		obj = l->addr;
		if (strcmp(path, obj->path) == 0)
			return (obj);
		l = l->next;
	}
	return (NULL);
}

void	*load_meshes(void *m)
{
	t_app	*app;
	t_list	*models;
	int		i;

	app = (t_app*)m;
	i = 0;
	models = app->models;
	while (models)
	{
		model_load(models->addr);
		models = models->next;
		i++;
	}
	return (NULL);
}
