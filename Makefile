NAME =			fdf

HEAD =			fdf.h

LIBDIR = 		./libft/

LIBFT = 		libft.a

HEAD_BONUS =	fdf_bonus.h

SRC = 			fdf.c			fdf_parser.c		fdf_utils.c			fdf_keyboard.c \
				fdf_grafical.c	fdf_gradient.c	

SRC_BONUS =		fdf_bonus.c				fdf_parser_bonus.c		fdf_utils_bonus.c	fdf_keyboard_bonus.c \
				fdf_grafical_bonus.c	fdf_gradient_bonus.c

OBJ =			$(SRC:%.c=%.o)

OBJ_BONUS =		$(SRC_BONUS:%.c=%.o)

D =				$(SRC:%.c=%.d)

D_BONUS =		$(SRC_BONUS:%.c=%.d)

CFLAGS = 		-Wall -Werror -Wextra -MD -I./libft/

CC = 			gcc

RM = 			rm -f

all : 			libmake $(NAME)

$(NAME) : 		$(OBJ)
				@cp $(LIBDIR)$(LIBFT) .
				$(CC) $(CFLAGS) $(OBJ) libft.a -lmlx -framework OpenGL -framework AppKit -o $@

libmake :
				@make -C $(LIBDIR)

%.o : 			%.c
				$(CC) $(CFLAGS) -Imlx -I $(HEAD) -c $< -o $@

include 		$(wildcard $(D) $(D_BONUS))

bonus:
				@make OBJ="$(OBJ_BONUS)" HEAD="$(HEAD_BONUS)" all

clean:
				@make clean -C $(LIBDIR)
				@$(RM) $(OBJ) $(D) $(D_BONUS) $(OBJ_BONUS)

fclean: 		clean
				@$(RM) $(NAME) $(LIBFT)

re: 			fclean all

.PHONY: 		all clean fclean re bonus
