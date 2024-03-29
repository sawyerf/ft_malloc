ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME =		libft_malloc_$(HOSTTYPE).so

CC =		gcc

INC_DIR =	inc

INC_FILE =	ft_malloc.h
		
SRC_DIR =	src

SRC_FILE =	malloc.c \
			ft_malloc.c \
			allocZone.c \
			freeZone.c \
			zone.c \
			debug.c \
			show_alloc_mem.c \

CFLAGS =	-I $(INC_DIR) -I libft/inc/ -Wall -lm -Werror -Wextra -g

OBJ_DIR =	.obj
OBJ_FILE =	$(SRC_FILE:.c=.o)

CRT_DIR =	./

SRC = 		$(addprefix $(SRC_DIR)/,$(SRC_FILE))
INC = 		$(addprefix $(INC_DIR)/,$(INC_FILE))
OBJ = 		$(addprefix $(OBJ_DIR)/,$(OBJ_FILE))
CRT = 		$(addprefix $(OBJ_DIR)/,$(CRT_DIR))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC) Makefile
	@printf "\033[0;32m[$(NAME)] Compilation [o.]\033[0;0m\r"
	@mkdir -p $(CRT) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@ -fPIC
	@printf "\033[0;32m[$(NAME)] Compilation [.o]\033[0;0m\r"

norm:
	@norminette $(SRC)
	@norminette $(INC)

testo:
	@printf "\033[0;32m[$(NAME)] Compilation [..]\033[0;0m\r"
	@gcc srcTest/myTest.c -o myTest -L. -l:libft_malloc.so -I inc/
	@gcc srcTest/test.c -o test
	@gcc srcTest/test1.c -o test1
	@gcc srcTest/test2.c -o test2
	@gcc srcTest/test3.c -o test3
	@gcc srcTest/test3bis.c -o test3bis
	@gcc srcTest/test4.c -o test4
	@gcc srcTest/test5.c -o test5 -L. -l:libft_malloc.so -I inc/
	@gcc srcTest/testThread.c -o testThread -lpthread
	@printf "\033[0;32m[$(NAME)] Compilation [OK]\033[0;0m\n"

$(NAME): $(OBJ)
	@printf "\033[0;32m[$(NAME)] Compilation [OK]\033[0;0m\n"
	@make -C libft/
	@$(CC) $(CFLAGS) -shared -o $@ $(OBJ) libft/libft.a
	@ln -s $@ libft_malloc.so 2>&- || true

clean:
	@make clean -C libft/
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf $(OBJ_DIR)
	@/bin/rm -f test test1 test2 test3 test3bis test4 test5 testThread myTest
	@/bin/rm -f libft_malloc.so $(NAME)
	@printf "\033[0;31m[$(NAME)] Deleted *.o\033[0;0m\n"

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f libft/libft.a
	@printf "\033[0;31D[$(NAME)] Deleted 42sh\033[0;0m\n"

re: fclean all

.PHONY: all clean fclean re
