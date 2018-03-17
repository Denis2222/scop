#include <scop.h>
#include <string.h>

long		getFileSize(FILE* pFile)
{
    long length = 0;

    fseek(pFile,0,SEEK_END);
    length = ftell(pFile);
    fseek(pFile,0,SEEK_SET);
    return (length);
}

void		add_shader(const char *path, GLuint program_id)
{
	t_app		*app;
	t_shader	*shader;

	shader = (t_shader*)malloc(sizeof(t_shader));
	shader->path = strdup(path);
	shader->loaded = 1;
	shader->program_id = program_id;
	app = root();
	list_push(&app->shaders, list_new(shader, sizeof(t_shader*)));
}

t_shader	*get_shader(const char *path)
{
	t_app		*app;
	t_list		*l;
	t_shader	*shader;

	app = root();
	l = app->shaders;
	while (l)
	{
		shader = l->addr;
		if (strcmp(path, shader->path) == 0)
			return (shader);
		l = l->next;
	}
	return (NULL);
}

GLuint shader_load(const char *name)
{
	t_shader	*shader;

	if ((shader = get_shader(name)))
		return (shader->program_id);

	char vertex_file_path[1024];
	char fragment_file_path[1024];

	sprintf(vertex_file_path, "./shaders/%s.vert", name);
	sprintf(fragment_file_path, "./shaders/%s.frag", name);

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	FILE *vertFile;
	FILE *fragFile;

	long vertFileSize;
	long fragFileSize;

	GLchar* log = NULL;

	vertFile = fopen(vertex_file_path, "r");
	if (vertFile == NULL)
	{
		printf("Can't read shader file : %s\n", vertex_file_path);
		return (0);
	}
	vertFileSize = getFileSize(vertFile);
	char *vertFileStr = NULL;
	vertFileStr = malloc(vertFileSize + 1);
	bzero(vertFileStr, vertFileSize + 1);
	if (!vertFileStr)
		exit(1);
	fread(vertFileStr, vertFileSize, 1, vertFile);
	fclose(vertFile);
	fragFile = fopen(fragment_file_path, "r");
	if (fragFile == NULL)
	{
		printf("Can't read shader file : %s\n", fragment_file_path);
		return (0);
	}
	fragFileSize = getFileSize(fragFile);
	char *fragFileStr = NULL;
	fragFileStr = malloc(fragFileSize + 1);
	if (!fragFileStr)
		exit(1);
	bzero(fragFileStr, fragFileSize + 1);
	fread(fragFileStr, fragFileSize, 1, fragFile);
	fclose(fragFile);
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = vertFileStr;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		printf("InfoLof");
		log = (GLchar*)malloc(InfoLogLength);
		if ( log == NULL )
		{
			fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
		}
		bzero(log, InfoLogLength);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, &InfoLogLength, log);
		fprintf(stderr,"Erreur de compilation:\n%s",log);
		free(log);
	}
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = fragFileStr;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		log = (GLchar*)malloc(InfoLogLength);
		if ( log == NULL )
		{
			fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
		}
		bzero(log, InfoLogLength);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, &InfoLogLength, log);
		fprintf(stderr,"Erreur de compilation:\n%s",log);
		free(log);
	}
	// Link the program
	printf("Linking program\n");
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, VertexShaderID);
	glAttachShader(program_id, FragmentShaderID);
	glLinkProgram(program_id);
	// Check the program
	glGetProgramiv(program_id, GL_LINK_STATUS, &Result);
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		log = (GLchar*)malloc(InfoLogLength);
		bzero(log, InfoLogLength);
		if ( log == NULL )
		{
			fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
		}
		glGetShaderInfoLog(program_id, InfoLogLength, &InfoLogLength, log);
		// On peut afficher le message
		if (strlen(log))
			fprintf(stderr,"Erreur de link:\n%s",log);
		// Et on n'oublie pas de libéré la mémoire
		free(log);
	}
	free(vertFileStr);
	free(fragFileStr);
	glDetachShader(program_id, VertexShaderID);
	glDetachShader(program_id, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	//pthread_mutex_unlock (&mutex_stock);

	//Add to app list;
	add_shader(name, program_id);

	return (program_id);
}
