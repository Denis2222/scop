SRCS = src/t_vec2f.c \
	   src/t_vec3f.c \
	   src/t_vec4f.c \
	   src/t_mat4f.c


LIBA = libglmc.a
NAME = $(LIBA)
GCC_FLAGS = -Wall -Werror -Wextra -I. -O3
CC = gcc $(GCC_FLAGS)
SRCDIR = ./
OBJDIR = ./
AR = ar -cq
RM = rm -rf
# standart
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@ranlib $@
	@echo "[$@] Complete"

$(addprefix $(OBJDIR)/, %.o): $(addprefix $(SRCDIR)/, %.c)
	@mkdir -p $(OBJDIR)
	@$(CC) -I. -o $@ -c $^

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(LIBA)

re: fclean all
