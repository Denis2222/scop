SRCS = put/ft_putchar.c \
	   put/ft_putstr.c \
	   put/ft_putnbr.c \
	   put/ft_putptr.c \
	   put/ft_putendl.c \
	   put/ft_putchar_fd.c \
	   put/ft_putstr_fd.c \
	   put/ft_putendl_fd.c \
	   put/ft_putnbr_fd.c \
	   put/ft_putulongnbr.c \
	   is/ft_isprint.c \
	   is/ft_isdigit.c \
	   is/ft_isalpha.c \
	   is/ft_isalnum.c \
	   is/ft_isascii.c \
	   is/ft_isupper.c \
	   is/ft_islower.c \
	   is/ft_isblank.c \
	   is/ft_isspace.c \
	   str/ft_strcmp.c \
	   str/ft_streachr.c \
	   str/ft_strcountchr.c \
	   str/ft_strlen.c \
	   str/ft_strcat.c \
	   str/ft_strcmp.c \
	   str/ft_strcpy.c \
	   str/ft_strdup.c \
	   str/ft_strlen.c \
	   str/ft_strncat.c \
	   str/ft_strncmp.c \
	   str/ft_strncpy.c \
	   str/ft_strrev.c \
	   str/ft_strstr.c \
	   str/ft_strnstr.c \
	   str/ft_strchr.c \
	   str/ft_strrchr.c \
	   str/ft_strrepchrbystr.c \
	   str/ft_strlcat.c \
	   str/ft_strnew.c \
	   str/ft_strdel.c \
	   str/ft_strclr.c \
	   str/ft_striter.c \
	   str/ft_striteri.c \
	   str/ft_strmap.c \
	   str/ft_strmapi.c \
	   str/ft_strequ.c \
	   str/ft_strnequ.c \
	   str/ft_strsub.c \
	   str/ft_strjoin.c \
	   str/ft_strtrim.c \
	   str/ft_strsplit.c \
	   str/ft_strrepchr.c \
	   mem/ft_memset.c \
	   mem/ft_memalloc.c \
	   mem/ft_memdel.c \
	   mem/ft_memcpy.c \
	   mem/ft_memccpy.c \
	   mem/ft_memcmp.c \
	   mem/ft_memmove.c \
	   mem/ft_memchr.c \
	   ft_atoi.c \
	   ft_bzero.c \
	   ft_tolower.c \
	   ft_toupper.c \
	   ft_tabfree.c \
	   ft_itoa.c \
	   ft_sqrt.c \
	   ft_tablen.c \
	   ft_abs.c \
	   ft_pow.c \
	   argvise.c

LIBA = libft.a
NAME = $(LIBA)
GCC_FLAGS = -Wall -Werror -Wextra
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
