NAME			=	libftprintf.a

CC				=	gcc
CFLAGS			=	-Wall -Werror -Wextra -I$(INC_DIR)

SRC_DIR			=	./src/
SRCS			=	$(addprefix $(SRC_DIR), $(SRC))
SRC				=	ft_printf.c

OBJ_DIR			=	./obj/
OBJ_DIR_PRINTF	=	$(OBJ_DIR)ft_printf/
OBJS			=	$(addprefix $(OBJ_DIR), $(OBJ))
OBJ				=	$(SRC:.c=.o)

INC_DIR			=	./include/
INCS			=	$(addprefix $(INC_DIR), $(INC))
INC				=	ft_printf.h

.PHONY: all clean fclean re

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c $(INCS)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR_PRINTF)

clean:
	@rm -f $(OBJS)
	@rm -rf $(OBJ_DIR)

fclean:				clean
	@rm -f $(NAME)

re:					fclean all