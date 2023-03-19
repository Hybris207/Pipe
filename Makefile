NAME		=	pipex

LIBFT		=	 libftt/ft_atoi.c libftt/ft_bzero.c libftt/ft_calloc.c libftt/ft_isalnum.c libftt/ft_isalpha.c libftt/ft_isascii.c libftt/ft_isdigit.c libftt/ft_isprint.c libftt/ft_itoa.c libftt/ft_memchr.c \
                 libftt/ft_memcmp.c libftt/ft_memcpy.c libftt/ft_memmove.c libftt/ft_memset.c libftt/ft_putchar_fd.c libftt/ft_putendl_fd.c libftt/ft_putnbr_fd.c libftt/ft_putstr_fd.c libftt/ft_split.c \
                 libftt/ft_strchr.c libftt/ft_strrchr.c libftt/ft_strdup.c libftt/ft_striteri.c libftt/ft_strjoin.c libftt/ft_strlcat.c libftt/ft_strlcpy.c libftt/ft_strlen.c libftt/ft_strmapi.c libftt/ft_strncmp.c \
                 libftt/ft_strnstr.c libftt/ft_strtrim.c libftt/ft_substr.c libftt/ft_tolower.c libftt/ft_toupper.c libftt/ft_strcmp.c

SRCS		=	main.c parcing.c pipes_utils.c command_line.c path_finder.c utils.c execution.c alpha_fork.c command_call.c redirection_alpha_fork.c utils_fork.c \
				check_everythings_is_okay.c

OBJS		=	${SRCS:.c=.o} ${LIBFT:.c=.o}

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g3
RM			=	rm -f

%.o: %.c
				${CC} ${CFLAGS} -c $< -o $@

all:			${NAME}

${NAME}:		${OBJS}
				${CC} ${CFLAGS} -o ${NAME} ${OBJS} -I/usr/local/include -lreadline

clean:
				rm -f $(OBJS)
fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
