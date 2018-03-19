UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	GCC_FLAG =  -fsanitize=address -g
	DL_INC = -Iexternal/glfw-3.1.2/include -I./includes -I./glmc -I./libft
	DL_FLAG = -L./glmc -L./libft -lglmc -lGLU -lGL -Lexternal/glfw-3.1.2/src -lglfw3 -lGLEW -lGLU -lGL -lXrandr -ldl -lm -lpthread -lXinerama -lXi -lXxf86vm -lXcursor -lX11
endif
ifeq ($(UNAME), Darwin)
	GCC_FLAG =  -Wall -Werror -Wextra -g -fsanitize=address
	DL_INC = -I./includes -I./glmc -I./libft -I $(HOME)/.brew/include
	DL_FLAG = -L./glmc -L./libft -L $(HOME)/.brew/lib -framework OpenGL -lglfw -lGLEW -lpthread
endif


CC = gcc $(GCC_FLAG) $(DL_INC)

NAME = scop

dir_guard=@mkdir -p $(@D)

GLMC = ./glmc/libglmc.a

LIBFT = ./libft/libft.a

SRC = shader.c \
	   Control/controls.c \
	   Control/control_light.c \
	   Control/control_options.c \
	   Control/control_view.c \
	   Model/model.c \
	   Model/model_bind.c \
	   Model/model_bind_buffer.c \
	   Model/model_generate.c \
	   Model/model_send.c \
	   Model/model_control.c \
	   Model/model_free.c \
	   glfw.c \
	   Object/obj.c \
	   Object/obj_center.c \
	   Object/obj_init.c \
	   Object/parsing.c \
	   Object/tangent.c \
	   Object/mesh_list.c \
	   Object/Parsing/face.c \
	   Object/Parsing/face_346.c \
	   Object/Parsing/tmp_obj.c \
	   t_list.c \
	   t_list2.c \
	   Material/mtl.c \
	   Material/bmp.c \
	   Material/texture.c \
	   root.c \
	   main.c

SRCDIR = ./srcs
OBJDIR = ./objs

SRCS=$(addprefix $(SRCDIR),$(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

all:$(NAME) $(GLMC) $(LIBFT)
	@if [ -a ./assets/AK ]; then echo "Assets OK"; else echo "Download Assets : " ; curl -O http://denis-moureu.fr/42/assets-scop.zip; echo "Unzip to ./assets/" ;unzip assets-scop.zip -d ./assets ; rm -rf ./assets-scop.zip ; fi;
$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	$(dir_guard)
	@$(CC)  -o $@ -c $^

$(NAME): $(OBJS) $(GLMC) $(LIBFT)
	@$(CC) -o $@ $^  $(DL_FLAG)
	@echo "[$@] Complete"

$(GLMC):
	@make -C ./glmc

$(LIBFT):
	@make -j99 -C ./libft

clean:
	@rm -rf $(OBJDIR)
	@make -C ./glmc clean
	@make -C ./libft clean

fclean: clean
	@rm -f $(NAME)
	@make -C ./glmc fclean
	@make -C ./libft fclean

re: fclean all
