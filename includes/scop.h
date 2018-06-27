/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:25:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 17:17:36 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOP_H
# define SCOP_H

# ifdef __linux__
#  define GL3_PROTOTYPES 1
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#  define OPENGL_VERSION_MAJOR 3
#  define OPENGL_VERSION_MINOR 3
# endif

# ifdef __APPLE__
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#  define OPENGL_VERSION_MAJOR 4
#  define OPENGL_VERSION_MINOR 3
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <glmc.h>
# include <libft.h>
# define WIDTH 800
# define HEIGHT 400
# define TITLE "Scop = [] => * "
# define BASE_FOV 45.0f

typedef struct		s_list
{
	void			*addr;
	unsigned int	value;
	size_t			size;
	struct s_list	*next;
}					t_list;

t_list				*list_new(void *addr, size_t size);
t_list				*list_new_uint(unsigned int u, size_t size);
int					list_length(t_list *list);
void				list_push(t_list **lst, t_list *to_add);
void				list_push_back(t_list *l, t_list *to_add);

void				*list_get(t_list *l, size_t n);

void				list_del(t_list **l);
void				list_del_one(t_list **l);

typedef struct		s_app
{
	unsigned int	width;
	unsigned int	height;
	GLFWwindow		*window;
	struct s_input	*input;

	t_list			*models;

	t_list			*textures;
	t_list			*shaders;
	t_list			*objs;

	t_argvise		*args;
}					t_app;

typedef struct		s_texture
{
	char			*path;
	int				loaded;
	unsigned char	*data;
	size_t			width;
	size_t			height;
	GLuint			texture_id;
}					t_texture;

typedef struct		s_shader
{
	char			*path;
	int				loaded;
	GLuint			program_id;
}					t_shader;

typedef struct		s_mtl
{
	char			*name;
	float			ns;
	t_vec3f			*ka;
	t_vec3f			*kd;
	t_vec3f			*ks;
	t_vec3f			*ke;
	float			ni;
	float			d;
	int				illum;

	char			*map_kd_path;
	char			*map_ks_path;
	char			*map_bump_path;

	unsigned char	*map_kd_buffer;
	unsigned char	*map_ks_buffer;
	unsigned char	*map_bump_buffer;

	GLuint			map_kd;
	GLuint			map_ks;
	GLuint			map_bump;

}					t_mtl;

typedef struct		s_obj
{
	char			*path;
	t_mtl			*mtl;
	float			*vertices;
	size_t			nvertices;
	float			*uvs;
	size_t			nuvs;
	float			*normals;
	size_t			nnormals;

	float			*tangents;
	float			*bitangents;

	float			*colors;
}					t_obj;

typedef struct		s_tmp_obj
{
	FILE			*file;

	char			*path;
	int				res;

	t_vec3f			*vertex;
	t_vec2f			*uv;
	t_vec3f			*normal;

	t_list			*temp_vertex;
	t_list			*temp_uv;
	t_list			*temp_normal;

	t_list			*vertex_indices;
	t_list			*uv_indices;
	t_list			*normal_indices;

	int				facefound;
	char			line_header[1024];
	char			stupid_buffer[1000];

	int				matches;

	unsigned int	vertex_index[4];
	unsigned int	uv_index[4];
	unsigned int	normal_index[4];

	long			read_head;

	int				vertex_i;
	int				uv_i;
	int				normal_i;

	t_mtl			*mtl;

	unsigned int	n;
	t_list			*vi;
	t_list			*ui;
	t_list			*ni;
}					t_tmp_obj;

typedef struct		s_input
{
	float			horizontal_angle;
	float			vertical_angle;
	float			initial_fov;
	float			speed;
	float			mouse_speed;

	double			last_time;

	int				view;

	t_vec3f			*pos;
	t_vec3f			*dir;
	t_vec3f			*right;

	t_vec3f			*delta_right;
	t_vec3f			*delta_dir;

	t_vec3f			*light_pos;

	float			ratio_color_texture;
	int				ratio_color_bool;
	float			var;

	int				auto_rotate;
	int				skybox;

	GLenum			render_mode;
}					t_input;

typedef struct		s_model
{
	t_obj			*obj_data;
	t_mtl			*mtl;

	char			*obj_filename;

	GLuint			vertexbuffer;
	GLuint			colorbuffer;
	GLuint			uvbuffer;
	GLuint			normalbuffer;

	GLuint			tangentbuffer;
	GLuint			bitangentbuffer;

	GLuint			program_id;

	GLuint			diffuse_texture;
	GLuint			diffuse_texture_id;

	GLuint			normal_texture;
	GLuint			normal_texture_id;

	GLuint			specular_texture;
	GLuint			specular_texture_id;

	GLuint			matrix_model_id;
	GLuint			matrix_view_id;
	GLuint			matrix_projection_id;

	GLuint			light_id;
	GLuint			ratio_colortexture_id;
	GLuint			camera_position_id;

	GLuint			model_scale_id;
	GLuint			model_rotate_id;
	GLuint			model_translate_id;

	t_vec3f			*position;
	t_vec3f			*rotation;
	t_vec3f			*scale;

	int				enable_uv;
	int				enable_normal;
	int				nvertices;

	t_vec3f			*vertex;
	t_vec3f			*color;
	t_vec2f			*uv;
	t_vec3f			*normal;
	t_vec3f			*tangent;
	t_vec3f			*bitangent;

	int				loaded;
	int				enable;

}					t_model;

t_app				*root(void);

int					init_glfw(t_app *app);
GLuint				shader_load(const char *name);

t_input				*camera_init(void);
void				camera_free(t_input *input);
void				camera_controls(t_app *app);
void				input_mousewheel(GLFWwindow *win, double x, double y);

void				add_texture(char *path, unsigned char *data, int width,
						int height);
t_texture			*get_texture(char *path);

t_model				*model_new(char *objfile);
t_model				*model_new_scale(char *objfile, float x, float y, float z);

int					model_load(t_model *model);

int					model_bind(t_model *model);
void				model_bind_buffer(GLuint *buffer, size_t s, float *data);
void				model_bind_texture(GLuint *texture_id, char *path);
int					model_bind_shader(t_model *model, char *name);
void				model_bind_buffer_all(t_model *model);

int					model_render(t_app *app, t_model *model);

void				model_generate_uniform_model(t_model *model);
void				model_generate_uniform_projection(t_app *app,
						t_model *model);
void				model_generate_uniform_view(t_app *app, t_model *model);

void				model_send_buffer(unsigned int attr, GLuint *buffer,
						size_t size);
void				model_send_texture(unsigned int i, GLuint texture,
						GLuint texture_id);
void				model_send_mvp(t_app *app, t_model *model);

void				model_control(t_app *app, t_model *model);
void				model_free(t_model *model);

int					model_load_obj(t_model *model, const char *path);

t_mtl				*new_mtl(char *path, t_tmp_obj *t);

char				*load_texture(char *path, t_tmp_obj *t);

void				compute_tangent(t_obj *o);
void				parse_face_3_4(FILE *file, t_tmp_obj *t);
void				parse_face_6(t_tmp_obj *t);
void				parse_face_8(t_tmp_obj *t);
void				parse_face_8_6(FILE *file, t_tmp_obj *t);
void				parse_face_9(t_tmp_obj *t);
void				parse_face_12(t_tmp_obj *t);
int					parse_face(FILE *file, t_tmp_obj *t);

void				parse_v(FILE *file, t_tmp_obj *t);
void				parse_vt(FILE *file, t_tmp_obj *t);
void				parse_vn(FILE *file, t_tmp_obj *t);
void				parse_mtl(FILE *file, t_tmp_obj *t);

int					tmp_obj_init(t_tmp_obj *t, const char *path);
int					tmp_obj_loading(t_tmp_obj *t);
void				tmp_obj_free(t_tmp_obj *t);

char				*ft_dirname(const char *filepath);

FILE				*open_file_from_folder(const char *folder, char *path);

int					load_bmp(const char *imagepath);

void				centerobj(t_obj *obj);
void				obj_init(t_obj *obj_data, t_tmp_obj *t);
void				obj_init_color(t_obj *obj_data);
t_obj				*secure_malloc_obj(void);

void				add_mesh(t_obj *obj, const char *path);
t_obj				*get_mesh(const char *path);

void				light_controls(t_app *app);
void				controls_direction(t_app *app);
void				control_render_mode(t_app *app);
void				control_color_texture(t_app *app);
void				control_auto_rotate(t_app *app);
void				control_view(t_app *app);

void				*load_meshes(void *m);

static int			g_oldstate;

#endif
