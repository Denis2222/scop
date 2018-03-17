#include <glmc.h>

t_vec4f	*vec4f(float x, float y, float z, float w)
{
	t_vec4f *n;

	n = (t_vec4f*)malloc(sizeof(t_vec4f));
	if (!n)
		return (NULL);
	n->x = x;
	n->y = y;
	n->z = z;
	n->w = w;
	return (n);
}

float	vec4f_sqrt(t_vec4f *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w);
}

float	vec4f_dot(t_vec4f *s, t_vec4f *d)
{
	return (s->x * d->x + s->y * d->y + s->z * d->z + s->w * d->w);
}

t_vec4f	*vec4f_norm(t_vec4f *v)
{
	float	n;

	n = sqrt(vec4f_sqrt(v));
	v->x /= n;
	v->y /= n;
	v->z /= n;
	v->w /= n;
	return (v);
}

t_vec4f	*vec4f_cross(t_vec4f *s, t_vec4f *d)
{
	float nx = s->y * d->z - s->z * d->y;
	float ny = s->z * d->x - s->x * d->z;
	float nz = s->x * d->y - s->y * d->x;
	float nw = s->w * d->w - s->w * d->w;
	return (vec4f(nx, ny, nz, nw));
}

void vec4f_print(t_vec4f *t) {
	printf("[x:%0.1f, y:%0.1f, z:%0.1f, w:%0.1f]\n", t->x, t->y, t->z, t->w);
}
