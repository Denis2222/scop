#include <scop.h>
#include <string.h>

long getFileSize(FILE* pFile)
{
    long length = 0;

    fseek(pFile,0,SEEK_END);
    length = ftell(pFile);
    fseek(pFile,0,SEEK_SET);
    return length;
}

char *load_shader_file(char *path)
{
	FILE	*vertFile;
	long	vertFileSize;
	char	*vertFileStr = NULL;

	vertFile = fopen(path, "r");
	if (vertFile == NULL)
	{
		printf("Can't read shader file : %s\n", path);
		return (0);
	}
	vertFileSize = getFileSize(vertFile);

	vertFileStr = malloc(vertFileSize + 1);
	bzero(vertFileStr, vertFileSize + 1);
	if (!vertFileStr)
		exit(1);
	fread(vertFileStr, vertFileSize, 1, vertFile);
	fclose(vertFile);
	return (vertFileStr);
}

GLuint shader_compile(char *FileStr)
{
	GLint	Result;
	int		InfoLogLength;
	GLuint	ShaderID;
	GLchar	*log;

	Result = GL_FALSE;
	ShaderID = glCreateShader(GL_VERTEX_SHADER);

	char const * SourcePointer = FileStr;
	glShaderSource(ShaderID, 1, &SourcePointer , NULL);
	glCompileShader(ShaderID);


	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		log = (GLchar*)malloc(InfoLogLength);
		if ( log == NULL )
		{
			fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
		}
		bzero(log, InfoLogLength);
		glGetShaderInfoLog(ShaderID, InfoLogLength, &InfoLogLength, log);
		fprintf(stderr,"Erreur de compilation Compil:\n%s",log);
		free(log);
	}
	return (ShaderID);
}

GLuint shader_load(const char *name) {

	char vertex_file_path[1024];
	char fragment_file_path[1024];
	GLchar	*log;
	GLint	Result;

	sprintf(vertex_file_path, "./shaders/%s.vert", name);
	sprintf(fragment_file_path, "./shaders/%s.frag", name);

	// Create the shaders

	char *vertFileStr = load_shader_file(vertex_file_path);
	char *fragFileStr = load_shader_file(fragment_file_path);

	GLuint FragmentShaderID;
	GLuint VertexShaderID;

	VertexShaderID = shader_compile(vertFileStr);
	FragmentShaderID = shader_compile(fragFileStr);


	GLuint ProgramID = glCreateProgram();

	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	Result = GL_FALSE;
	int		InfoLogLength;
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if ( InfoLogLength > 0 ){
		log = (GLchar*)malloc(InfoLogLength);
		if ( log == NULL )
		{
			fprintf(stderr,"Erreur d'allocation de mémoire pour le log de la compilation du shader\n");
			return 0;
		}
		//bzero(log, InfoLogLength);
		glGetShaderInfoLog(ProgramID, InfoLogLength, &InfoLogLength, log);
		fprintf(stderr,"LogLength  %d Erreur de compilation LINK:\n%s",InfoLogLength,log);
		// Et on n'oublie pas de libéré la mémoire
		free(log);
	}


	free(vertFileStr);
	free(fragFileStr);
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	//pthread_mutex_unlock (&mutex_stock);
	return ProgramID;
}
