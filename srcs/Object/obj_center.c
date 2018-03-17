/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_center.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:33:22 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 12:33:55 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <scop.h>

void	centerobj_minmax(t_obj *obj, t_vec3f *min, t_vec3f *max)
{
	t_vec3f	*v;
	size_t	i;

	i = 0;
	while (i < obj->nvertices * 3)
	{
		v = (t_vec3f*)&obj->vertices[i];
		if (max->x < v->x)
			max->x = v->x;
		if (max->y < v->y)
			max->y = v->y;
		if (max->z < v->z)
			max->z = v->z;
		if (min->x > v->x)
			min->x = v->x;
		if (min->y > v->y)
			min->y = v->y;
		if (min->z > v->z)
			min->z = v->z;
		i += 3;
	}
}

void	centerobj(t_obj *obj)
{
	size_t	i;
	t_vec3f	max;
	t_vec3f	min;
	t_vec3f	*v;
	t_vec3f *mintomax;

	vec3fedit(&max, -1e20f, -1e20f, -1e20f);
	vec3fedit(&min, 1e20f, 1e20f, 1e20f);
	centerobj_minmax(obj, &min, &max);
	mintomax = vec3f_new_sub(&max, &min);
	mintomax = vec3f_scale(mintomax, 0.5f);
	mintomax = vec3f_add(mintomax, &min);
	i = 0;
	while (i < obj->nvertices * 3)
	{
		v = (t_vec3f*)&obj->vertices[i];
		vec3f_sub(v, mintomax);
		i += 3;
	}
	free(mintomax);
}
