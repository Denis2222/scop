/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scop.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoureu- <dmoureu-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:25:14 by dmoureu-          #+#    #+#             */
/*   Updated: 2018/03/17 15:35:50 by dmoureu-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCOOP_H
# define SCOOP_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <libgen.h>
# include <pthread.h>
# ifdef __linux__
#  define GL3_PROTOTYPES 1
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#  define OPENGL_VERSION_MAJOR 3
#  define OPENGL_VERSION_MINOR 3
# else
#  include <GL/glew.h>
#  include <GLFW/glfw3.h>
#  define OPENGL_VERSION_MAJOR 4
#  define OPENGL_VERSION_MINOR 0
# endif
# include <glmc.h>
# include <libft.h>
# define WIDTH 2000
# define HEIGHT 1000
# define TITLE "Scop = [] => * "
# define BASE_FOV 45.0f

typedef struct		s_list
{
	void			*addr;
	unsigned int	value;
	size_t			size;
	struct s_list	*next;
}					t_list;

t_list	*list_new(void *addr, size_t size);
t_list	*list_new_uint(unsigned int u, size_t size);
int		list_length(t_list *list);
void	list_push(t_list **lst, t_list *to_add);
void	list_push_back(t_list *l, t_list *to_add);

void	*list_get(t_list *l, size_t n);

void	list_del(t_list **l);
void	list_del_one(t_list **l);

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

typedef struct 		s_texture
{
	char			*path;
	int				loaded;
	unsigned char	*data;
	size_t			width;
	size_t			height;
	GLuint			textureID;
}					t_texture;

typedef struct 		s_shader
{
	char			*path;
	int				loaded;
	GLuvoid			program_id;
}					t_shader;

typedef struct		s_mtl
{
	char			*name;
	float			Ns;
	t_vec3f			*Ka;
	t_vec3f			*Kd;
	t_vec3f			*Ks;
	t_vec3f			*Ke;
	float			Ni;
	float			d;
	int				illum;

	char			*map_Kd_path;
	char			*map_Ks_path;
	char			*map_Bump_path;

	unsigned char	*map_Kd_buffer;
	unsigned char	*map_Ks_buffer;
	unsigned char	*map_Bump_buffer;

	GLuint			map_Kd;
	GLuint			map_Ks;
	GLuint			map_Bump;

}					t_mtl;

typedef struct		s_obj
{
	char			*path;
	t_mtl			*mtl;
	float			*vertices;
	size_t			nvertices;
	float			*uvs;
	size_t			nuvs;
	float 			*normals;
	size_t			nnormals;

	float			*tangents;
	float 			*bitangents;

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

	t_list			*vertexIndices;
	t_list			*uvIndices;
	t_list			*normalIndices;

	void			facefound;
	char 			lineHeader[1024];
	char 			stupidBuffer[1000];

	void			matches;

	unsigned int	vertexIndex[4];
	unsigned int	uvIndex[4];
	unsigned int	normalIndex[4];

	long			readHead;

	int				vertexI;
	int				uvI;
	int				normalI;

	t_mtl			*mtl;

	unsigned int	n;
	t_list			*vI;
	t_list			*uI;
	t_list			*nI;
}					t_tmp_obj;

typedef struct		s_input
{
	float			horizontalAngle;
	float			verticalAngle;
	float			initialFoV;
	float			speed;
	float			mouseSpeed;

	double			lastTime;

	int				view;

	t_vec3f			*pos;
	t_vec3f			*dir;
	t_vec3f			*right;

	t_vec3f			*deltaRight;
	t_vec3f			*deltaDir;

	t_vec3f			*lightPos;

	float			RatioColorTexture;
	int				RatioColorTextureBool;
	float			var;

	int				autoRotate;
	int				skybox;

	GLenum			renderMode;
}					t_input;

typedef struct		s_model
{
	t_obj			*objData;
	t_mtl			*mtl;

	char			*obj_filename;

	GLuint			vertexbuffer;
	GLuint			colorbuffer;
	GLuint			uvbuffer;
	GLuint			normalbuffer;

	GLuint			tangentbuffer;
	GLuint			bitangentbuffer;

	GLuint			programID;

	GLuint			DiffuseTexture;
	GLuint			DiffuseTextureID;

	GLuint			NormalTexture;
	GLuint			NormalTextureID;

	GLuint			SpecularTexture;
	GLuint			SpecularTextureID;

	GLuint			MatrixModelID;
	GLuint			MatrixViewID;
	GLuint			MatrixProjectionID;

	GLuint			LightID;
	GLuint			RatioColorTextureID;
	GLuint			CameraPositionID;

	GLuint			ModelScaleID;
	GLuint			ModelRotateID;
	GLuint			ModelTranslateID;

	t_vec3f			*position;
	t_vec3f			*rotation;
	t_vec3f			*scale;

	int				enableUV;
	int				enableNormal;
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
GLuvoid				shader_load(const char *name);

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
void				model_bind_texture(GLuint *textureID, char *path);
int					model_bind_shader(t_model *model, char *name);
void		model_bind_buffer_all(t_model *model);

void		model_render(t_app *app, t_model *model);

void		model_generate_uniform_model(t_model *model);
void		model_generate_uniform_projection(t_app *app, t_model *model);
void		model_generate_uniform_view(t_app *app, t_model *model);

void		model_send_buffer(unsigned int attr, GLuint *buffer, size_t size);
void		model_send_texture(unsigned int i, GLuint Texture,
					GLuint TextureID);
void		model_send_mvp(t_app *app, t_model *model);

void		model_control(t_app *app, t_model *model);
void		model_free(t_model *model);

void		model_load_obj(t_model *model, const char *path);

t_mtl 		*new_mtl(char *path, t_tmp_obj *t);

char 		*load_texture(char *path, t_tmp_obj *t);

void		compute_tangent(t_obj *o);
void		parse_face_3_4(FILE *file, t_tmp_obj *t);
void		parse_face_6(t_tmp_obj *t);
void		parse_face_8(t_tmp_obj *t);
void		parse_face_8_6(FILE *file, t_tmp_obj *t);
void		parse_face_9(t_tmp_obj *t);
void		parse_face_12(t_tmp_obj *t);
int			parse_face(FILE *file, t_tmp_obj *t);

void		parse_v(FILE *file, t_tmp_obj *t);
void		parse_vt(FILE *file, t_tmp_obj *t);
void		parse_vn(FILE *file, t_tmp_obj *t);
void		parse_mtl(FILE *file, t_tmp_obj *t);

int			tmp_obj_init(t_tmp_obj *t, const char *path);
int			tmp_obj_loading(t_tmp_obj *t);
void		tmp_obj_free(t_tmp_obj *t);

char 		*ft_dirname(const char *filepath);

FILE		*open_file_from_folder(const char *folder, char *path);

int			load_bmp(const char * imagepath);

void		centerobj(t_obj *obj);
void		obj_init(t_obj *obj_data, t_tmp_obj *t);
void		obj_init_color(t_obj *obj_data);
t_obj		*secure_malloc_obj(void);

void		add_mesh(t_obj *obj, const char *path);
t_obj		*get_mesh(const char *path);

void		light_controls(t_app *app);
void		controls_direction(t_app *app);
void		control_render_mode(t_app *app);
void		control_color_texture(t_app *app);
void		control_auto_rotate(t_app *app);
void		control_view(t_app *app);

void		*load_meshes(void *m);

static void	oldState;

#endif
